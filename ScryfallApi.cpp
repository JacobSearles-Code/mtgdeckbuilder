#include "ScryfallApi.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ScryfallApi::ScryfallApi(QObject *parent)
    : QObject(parent)
{
}

CardModel *ScryfallApi::searchModel()
{
    return &m_searchModel;
}

bool ScryfallApi::loading() const
{
    return m_loading;
}

void ScryfallApi::searchCards(const QString &query)
{
    if (query.trimmed().isEmpty())
    {
        loadRecommendations();
        return;
    }

    performSearch(query);
}

void ScryfallApi::loadRecommendations()
{
    performSearch(
        "game:paper"
        );
}

void ScryfallApi::setCommanderColors(
    const QStringList &colors
    )
{
    m_commanderColors = colors;

    if (m_searchModel.count() == 0)
        return;

    QList<Card *> filteredCards;

    for (int i = 0; i < m_searchModel.count(); ++i)
    {
        Card *card = m_searchModel.cardAt(i);

        if (!card)
            continue;

        if (cardMatchesCommanderColors(card))
        {
            Card *copy = new Card(
                card->id(),
                card->name(),
                card->manaCost(),
                card->typeLine(),
                card->oracleText(),
                card->imageUrl(),
                card->colors(),
                card->colorIdentity()
                );

            filteredCards.append(copy);
        }
    }

    m_searchModel.setCards(filteredCards);
}

bool ScryfallApi::cardMatchesCommanderColors(
    Card *card
    ) const
{
    if (!card)
        return false;

    if (m_commanderColors.isEmpty())
        return true;

    for (const QString &color : card->colorIdentity())
    {
        if (!m_commanderColors.contains(color))
            return false;
    }

    return true;
}

void ScryfallApi::performSearch(
    const QString &query
    )
{
    m_loading = true;
    emit loadingChanged();

    QUrl url(
        "https://api.scryfall.com/cards/search"
        );

    QUrlQuery urlQuery;

    urlQuery.addQueryItem(
        "q",
        query
        );

    urlQuery.addQueryItem(
        "unique",
        "cards"
        );

    if (query == "game:paper")
    {
        urlQuery.addQueryItem(
            "order",
            "edhrec"
            );
    }
    else
    {
        urlQuery.addQueryItem(
            "order",
            "name"
            );
    }

    url.setQuery(urlQuery);

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::UserAgentHeader,
        "mtgDeckBuilder/1.0"
        );

    request.setRawHeader(
        "Accept",
        "application/json"
        );

    QNetworkReply *reply =
        m_networkManager.get(request);

    connect(
        reply,
        &QNetworkReply::finished,
        this,
        [this, reply]()
        {
            handleSearchResponse(reply);
        }
        );
}

void ScryfallApi::handleSearchResponse(
    QNetworkReply *reply
    )
{
    m_loading = false;
    emit loadingChanged();

    if (reply->error() != QNetworkReply::NoError)
    {
        emit searchError(
            reply->errorString()
            );

        reply->deleteLater();
        return;
    }

    const QByteArray data =
        reply->readAll();

    QJsonParseError parseError;

    QJsonDocument document =
        QJsonDocument::fromJson(
            data,
            &parseError
            );

    if (parseError.error != QJsonParseError::NoError)
    {
        emit searchError(
            "Could not parse Scryfall response."
            );

        reply->deleteLater();
        return;
    }

    QJsonObject root =
        document.object();

    QJsonArray cards =
        root.value("data").toArray();

    QList<Card *> results;

    for (const QJsonValue &value : cards)
    {
        if (!value.isObject())
            continue;

        Card *card =
            cardFromJson(
                value.toObject()
                );

        if (!card)
            continue;

        if (cardMatchesCommanderColors(card))
        {
            results.append(card);
        }
        else
        {
            delete card;
        }
    }

    m_searchModel.setCards(results);

    emit searchFinished();

    reply->deleteLater();
}

Card *ScryfallApi::cardFromJson(
    const QJsonObject &object
    )
{
    QString id =
        object.value("id").toString();

    QString name =
        object.value("name").toString();

    QString manaCost =
        object.value("mana_cost").toString();

    QString typeLine =
        object.value("type_line").toString();

    QString oracleText =
        object.value("oracle_text").toString();

    QString imageUrl;

    QJsonObject imageUris =
        object.value("image_uris").toObject();

    imageUrl =
        imageUris.value("normal").toString();

    QStringList colors;

    QJsonArray colorsArray =
        object.value("colors").toArray();

    for (const QJsonValue &color :
         colorsArray)
    {
        colors.append(
            color.toString()
            );
    }

    QStringList colorIdentity;

    QJsonArray identityArray =
        object.value(
                  "color_identity"
                  ).toArray();

    for (const QJsonValue &color :
         identityArray)
    {
        colorIdentity.append(
            color.toString()
            );
    }

    /*
     * Double-faced cards don't always have
     * image_uris directly on the card.
     */
    if (imageUrl.isEmpty())
    {
        QJsonArray faces =
            object.value(
                      "card_faces"
                      ).toArray();

        if (!faces.isEmpty())
        {
            QJsonObject face =
                faces.first().toObject();

            if (manaCost.isEmpty())
            {
                manaCost =
                    face.value(
                            "mana_cost"
                            ).toString();
            }

            if (oracleText.isEmpty())
            {
                oracleText =
                    face.value(
                            "oracle_text"
                            ).toString();
            }

            QJsonObject faceImages =
                face.value(
                        "image_uris"
                        ).toObject();

            imageUrl =
                faceImages.value(
                              "normal"
                              ).toString();
        }
    }

    if (id.isEmpty() || name.isEmpty())
        return nullptr;

    return new Card(
        id,
        name,
        manaCost,
        typeLine,
        oracleText,
        imageUrl,
        colors,
        colorIdentity
        );
}