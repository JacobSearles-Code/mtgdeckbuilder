#ifndef DECKMANAGER_H
#define DECKMANAGER_H

#include <QObject>
#include <QMap>
#include <QVariantList>
#include <QStringList>

#include "Card.h"

class DeckManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        int cardCount
            READ cardCount
                NOTIFY deckChanged
        )

    Q_PROPERTY(
        int commanderCount
            READ commanderCount
                NOTIFY deckChanged
        )

    Q_PROPERTY(
        QStringList commanderColors
            READ commanderColors
                NOTIFY deckChanged
        )

public:

    explicit DeckManager(QObject *parent = nullptr);

    ~DeckManager();

    int cardCount() const;

    int commanderCount() const;

    QStringList commanderColors() const;

    Q_INVOKABLE bool addCard(Card *card);

    Q_INVOKABLE bool addCommander(Card *card);

    Q_INVOKABLE void removeCard(
        const QString &id
        );

    Q_INVOKABLE void removeCommander(
        const QString &id
        );

    Q_INVOKABLE int quantity(
        const QString &id
        ) const;

    Q_INVOKABLE bool isInDeck(
        const QString &id
        ) const;

    Q_INVOKABLE bool isLegalForCommander(
        Card *card
        ) const;

    Q_INVOKABLE QString categoryForCard(
        Card *card
        ) const;

    Q_INVOKABLE QVariantList entries(
        const QString &category
        ) const;

    Q_INVOKABLE QVariantList commanders() const;

    Q_INVOKABLE void clearDeck();

    Q_INVOKABLE bool saveDeck(
        const QString &filePath
        );

    Q_INVOKABLE bool loadDeck(
        const QString &filePath
        );

    Q_INVOKABLE bool exportDeck(
        const QString &filePath
        );

signals:

    void deckChanged();

    void deckError(
        const QString &message
        );

private:

    struct DeckEntry
    {
        Card *card = nullptr;
        int quantity = 0;
    };

    Card *copyCard(
        Card *card
        ) const;

    void deleteDeckEntries();

    QMap<QString, DeckEntry> m_cards;

    QList<Card *> m_commanders;
};

#endif // DECKMANAGER_H