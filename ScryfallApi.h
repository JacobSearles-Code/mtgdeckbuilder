#ifndef SCRYFALLAPI_H
#define SCRYFALLAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QStringList>

#include "CardModel.h"

class ScryfallApi : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        CardModel* searchModel
            READ searchModel
                CONSTANT
        )

    Q_PROPERTY(
        bool loading
            READ loading
                NOTIFY loadingChanged
        )

public:

    explicit ScryfallApi(QObject *parent = nullptr);

    CardModel *searchModel();

    bool loading() const;

    Q_INVOKABLE void searchCards(
        const QString &query
        );

    Q_INVOKABLE void loadRecommendations();

    Q_INVOKABLE void setCommanderColors(
        const QStringList &colors
        );

signals:

    void loadingChanged();

    void searchFinished();

    void searchError(
        const QString &message
        );

private:

    void performSearch(
        const QString &query
        );

    void handleSearchResponse(
        QNetworkReply *reply
        );

    Card *cardFromJson(
        const QJsonObject &object
        );

    bool cardMatchesCommanderColors(
        Card *card
        ) const;

    QNetworkAccessManager m_networkManager;

    CardModel m_searchModel;

    bool m_loading = false;

    QStringList m_commanderColors;
};

#endif // SCRYFALLAPI_H