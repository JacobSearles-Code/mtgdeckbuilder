#include "CardModel.h"

CardModel::CardModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CardModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_cards.size();
}

QVariant CardModel::data(
    const QModelIndex &index,
    int role
    ) const
{
    if (!index.isValid() ||
        index.row() < 0 ||
        index.row() >= m_cards.size())
    {
        return {};
    }

    Card *card = m_cards.at(index.row());

    switch (role)
    {
    case IdRole:
        return card->id();

    case NameRole:
        return card->name();

    case ManaCostRole:
        return card->manaCost();

    case TypeLineRole:
        return card->typeLine();

    case OracleTextRole:
        return card->oracleText();

    case ImageUrlRole:
        return card->imageUrl();

    case ColorsRole:
        return card->colors();

    case ColorIdentityRole:
        return card->colorIdentity();

    default:
        return {};
    }
}

QHash<int, QByteArray> CardModel::roleNames() const
{
    return {
        { IdRole, "cardId" },
        { NameRole, "cardName" },
        { ManaCostRole, "manaCost" },
        { TypeLineRole, "typeLine" },
        { OracleTextRole, "oracleText" },
        { ImageUrlRole, "imageUrl" },
        { ColorsRole, "colors" },
        { ColorIdentityRole, "colorIdentity" }
    };
}

int CardModel::count() const
{
    return m_cards.size();
}

Card *CardModel::cardAt(int index) const
{
    if (index < 0 || index >= m_cards.size())
        return nullptr;

    return m_cards.at(index);
}

void CardModel::setCards(const QList<Card *> &cards)
{
    beginResetModel();

    qDeleteAll(m_cards);
    m_cards.clear();

    for (Card *card : cards)
    {
        if (card)
        {
            card->setParent(this);
            m_cards.append(card);
        }
    }

    endResetModel();

    emit countChanged();
}

void CardModel::clear()
{
    beginResetModel();

    qDeleteAll(m_cards);
    m_cards.clear();

    endResetModel();

    emit countChanged();
}