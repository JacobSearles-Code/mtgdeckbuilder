#include "DeckManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

DeckManager::DeckManager(QObject *parent)
    : QObject(parent)
{
}

DeckManager::~DeckManager()
{
    deleteDeckEntries();

    qDeleteAll(m_commanders);
    m_commanders.clear();
}

void DeckManager::deleteDeckEntries()
{
    for (auto &entry : m_cards)
    {
        delete entry.card;
        entry.card = nullptr;
    }

    m_cards.clear();
}

Card *DeckManager::copyCard(Card *card) const
{
    if (!card)
        return nullptr;

    return new Card(
        card->id(),
        card->name(),
        card->manaCost(),
        card->typeLine(),
        card->oracleText(),
        card->imageUrl(),
        card->colors(),
        card->colorIdentity()
        );
}

int DeckManager::cardCount() const
{
    int count = 0;

    for (const DeckEntry &entry : m_cards)
    {
        count += entry.quantity;
    }

    count += m_commanders.size();

    return count;
}

int DeckManager::commanderCount() const
{
    return m_commanders.size();
}

QStringList DeckManager::commanderColors() const
{
    QStringList result;

    for (Card *commander :
         m_commanders)
    {
        if (!commander)
            continue;

        for (const QString &color :
             commander->colorIdentity())
        {
            if (!result.contains(color))
                result.append(color);
        }
    }

    return result;
}

bool DeckManager::addCard(Card *card)
{
    if (!card)
        return false;

    // Commander + mainboard cards cannot exceed 100 cards.
    if (cardCount() >= 100)
    {
        emit deckError(
            "Your Commander deck already has 100 cards."
            );

        return false;
    }

    // Check commander color identity.
    if (!isLegalForCommander(card))
    {
        emit deckError(
            "This card is outside your commanders' color identity."
            );

        return false;
    }

    // Commander uses the singleton rule.
    //
    // Basic lands are the exception and can be
    // included multiple times.
    if (m_cards.contains(card->id()))
    {
        if (!card->typeLine().contains(
                "Basic Land",
                Qt::CaseInsensitive))
        {
            emit deckError(
                "Commander decks can only have one copy of this card."
                );

            return false;
        }

        // Basic land:
        // Increase its quantity.
        m_cards[card->id()].quantity++;
    }
    else
    {
        DeckEntry entry;

        entry.card = copyCard(card);
        entry.quantity = 1;

        m_cards.insert(
            card->id(),
            entry
            );
    }

    emit deckChanged();

    return true;
}

bool DeckManager::addCommander(Card *card)
{
    if (!card)
        return false;

    if (m_commanders.size() >= 2)
    {
        emit deckError(
            "You can only have two commanders."
            );

        return false;
    }

    if (!card->typeLine()
             .contains(
                 "Legendary",
                 Qt::CaseInsensitive
                 ))
    {
        emit deckError(
            "Commander must be a legendary card."
            );

        return false;
    }

    for (Card *commander :
         m_commanders)
    {
        if (commander->id() == card->id())
        {
            emit deckError(
                "That commander is already selected."
                );

            return false;
        }
    }

    m_commanders.append(
        copyCard(card)
        );

    emit deckChanged();

    return true;
}

void DeckManager::removeCard(
    const QString &id
    )
{
    if (!m_cards.contains(id))
        return;

    DeckEntry &entry =
        m_cards[id];

    entry.quantity--;

    if (entry.quantity <= 0)
    {
        delete entry.card;
        m_cards.remove(id);
    }

    emit deckChanged();
}

void DeckManager::removeCommander(
    const QString &id
    )
{
    for (int i = 0;
         i < m_commanders.size();
         ++i)
    {
        Card *commander =
            m_commanders.at(i);

        if (commander &&
            commander->id() == id)
        {
            delete commander;

            m_commanders.removeAt(i);

            emit deckChanged();

            return;
        }
    }
}

int DeckManager::quantity(
    const QString &id
    ) const
{
    if (!m_cards.contains(id))
        return 0;

    return m_cards.value(id).quantity;
}

bool DeckManager::isInDeck(
    const QString &id
    ) const
{
    return m_cards.contains(id);
}

bool DeckManager::isLegalForCommander(
    Card *card
    ) const
{
    if (!card)
        return false;

    QStringList colors =
        commanderColors();

    /*
     * No commander selected yet:
     * allow everything.
     */
    if (colors.isEmpty())
        return true;

    /*
     * Colorless cards are always legal.
     */
    if (card->colorIdentity().isEmpty())
        return true;

    /*
     * Every color in the card's
     * identity must be inside the
     * commander's identity.
     */
    for (const QString &color :
         card->colorIdentity())
    {
        if (!colors.contains(color))
            return false;
    }

    return true;
}

QString DeckManager::categoryForCard(
    Card *card
    ) const
{
    if (!card)
        return "Sideboard";

    const QString type =
        card->typeLine();

    if (type.contains(
            "Creature",
            Qt::CaseInsensitive))
    {
        return "Creature";
    }

    if (type.contains(
            "Instant",
            Qt::CaseInsensitive))
    {
        return "Instant";
    }

    if (type.contains(
            "Sorcery",
            Qt::CaseInsensitive))
    {
        return "Sorcery";
    }

    if (type.contains(
            "Enchantment",
            Qt::CaseInsensitive))
    {
        return "Enchantment";
    }

    if (type.contains(
            "Artifact",
            Qt::CaseInsensitive))
    {
        return "Artifact";
    }

    if (type.contains(
            "Land",
            Qt::CaseInsensitive))
    {
        return "Land";
    }

    return "Sideboard";
}

QVariantList DeckManager::entries(
    const QString &category
    ) const
{
    QVariantList result;

    for (const DeckEntry &entry :
         m_cards)
    {
        if (!entry.card)
            continue;

        if (categoryForCard(entry.card)
            != category)
        {
            continue;
        }

        QVariantMap item;

        item["id"] =
            entry.card->id();

        item["name"] =
            entry.card->name();

        item["quantity"] =
            entry.quantity;

        item["imageUrl"] =
            entry.card->imageUrl();

        item["typeLine"] =
            entry.card->typeLine();

        result.append(item);
    }

    return result;
}

QVariantList DeckManager::commanders() const
{
    QVariantList result;

    for (Card *commander :
         m_commanders)
    {
        if (!commander)
            continue;

        QVariantMap item;

        item["id"] =
            commander->id();

        item["name"] =
            commander->name();

        item["imageUrl"] =
            commander->imageUrl();

        item["typeLine"] =
            commander->typeLine();

        result.append(item);
    }

    return result;
}

void DeckManager::clearDeck()
{
    deleteDeckEntries();

    qDeleteAll(m_commanders);
    m_commanders.clear();

    emit deckChanged();
}

bool DeckManager::saveDeck(
    const QString &filePath
    )
{
    QJsonObject root;

    QJsonArray commanders;

    for (Card *commander :
         m_commanders)
    {
        if (!commander)
            continue;

        QJsonObject object;

        object["id"] =
            commander->id();

        object["name"] =
            commander->name();

        object["manaCost"] =
            commander->manaCost();

        object["typeLine"] =
            commander->typeLine();

        object["oracleText"] =
            commander->oracleText();

        object["imageUrl"] =
            commander->imageUrl();

        object["colors"] =
            QJsonArray::fromStringList(
                commander->colors()
                );

        object["colorIdentity"] =
            QJsonArray::fromStringList(
                commander->colorIdentity()
                );

        commanders.append(object);
    }

    root["commanders"] =
        commanders;

    QJsonArray cards;

    for (const DeckEntry &entry :
         m_cards)
    {
        if (!entry.card)
            continue;

        QJsonObject object;

        object["quantity"] =
            entry.quantity;

        object["id"] =
            entry.card->id();

        object["name"] =
            entry.card->name();

        object["manaCost"] =
            entry.card->manaCost();

        object["typeLine"] =
            entry.card->typeLine();

        object["oracleText"] =
            entry.card->oracleText();

        object["imageUrl"] =
            entry.card->imageUrl();

        object["colors"] =
            QJsonArray::fromStringList(
                entry.card->colors()
                );

        object["colorIdentity"] =
            QJsonArray::fromStringList(
                entry.card->colorIdentity()
                );

        cards.append(object);
    }

    root["cards"] =
        cards;

    QFile file(filePath);

    if (!file.open(
            QIODevice::WriteOnly))
    {
        emit deckError(
            "Could not save deck."
            );

        return false;
    }

    file.write(
        QJsonDocument(root)
            .toJson(
                QJsonDocument::Indented
                )
        );

    file.close();

    return true;
}

bool DeckManager::loadDeck(
    const QString &filePath
    )
{
    QFile file(filePath);

    if (!file.open(
            QIODevice::ReadOnly))
    {
        emit deckError(
            "Could not open deck file."
            );

        return false;
    }

    QByteArray data =
        file.readAll();

    file.close();

    QJsonParseError error;

    QJsonDocument document =
        QJsonDocument::fromJson(
            data,
            &error
            );

    if (error.error !=
        QJsonParseError::NoError)
    {
        emit deckError(
            "Invalid deck file."
            );

        return false;
    }

    clearDeck();

    QJsonObject root =
        document.object();

    QJsonArray commanders =
        root.value(
                "commanders"
                ).toArray();

    for (const QJsonValue &value :
         commanders)
    {
        QJsonObject object =
            value.toObject();

        QStringList colors =
            object.value(
                      "colors"
                      ).toVariant().toStringList();

        QStringList identity =
            object.value(
                      "colorIdentity"
                      ).toVariant().toStringList();

        Card *card =
            new Card(
                object["id"].toString(),
                object["name"].toString(),
                object["manaCost"].toString(),
                object["typeLine"].toString(),
                object["oracleText"].toString(),
                object["imageUrl"].toString(),
                colors,
                identity
                );

        m_commanders.append(card);
    }

    QJsonArray cards =
        root.value(
                "cards"
                ).toArray();

    for (const QJsonValue &value :
         cards)
    {
        QJsonObject object =
            value.toObject();

        QStringList colors =
            object.value(
                      "colors"
                      ).toVariant().toStringList();

        QStringList identity =
            object.value(
                      "colorIdentity"
                      ).toVariant().toStringList();

        Card *card =
            new Card(
                object["id"].toString(),
                object["name"].toString(),
                object["manaCost"].toString(),
                object["typeLine"].toString(),
                object["oracleText"].toString(),
                object["imageUrl"].toString(),
                colors,
                identity
                );

        DeckEntry entry;

        entry.card = card;
        entry.quantity =
            object["quantity"].toInt();

        m_cards.insert(
            card->id(),
            entry
            );
    }

    emit deckChanged();

    return true;
}

bool DeckManager::exportDeck(
    const QString &filePath
    )
{
    QFile file(filePath);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text))
    {
        emit deckError(
            "Could not export deck."
            );

        return false;
    }

    QTextStream stream(&file);

    stream << "Commander\n";

    for (Card *commander :
         m_commanders)
    {
        if (commander)
        {
            stream
                << "1 "
                << commander->name()
                << "\n";
        }
    }

    stream << "\nMainboard\n";

    QStringList categories = {
        "Creature",
        "Instant",
        "Sorcery",
        "Enchantment",
        "Artifact",
        "Land",
        "Sideboard"
    };

    for (const QString &category :
         categories)
    {
        QVariantList cards =
            entries(category);

        if (cards.isEmpty())
            continue;

        stream
            << "\n"
            << category
            << "\n";

        for (const QVariant &value :
             cards)
        {
            QVariantMap item =
                value.toMap();

            stream
                << item["quantity"].toInt()
                << " "
                << item["name"].toString()
                << "\n";
        }
    }

    file.close();

    return true;
}