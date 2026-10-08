#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "Card.h"

class CardModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:

    enum CardRoles
    {
        IdRole = Qt::UserRole + 1,
        NameRole,
        ManaCostRole,
        TypeLineRole,
        OracleTextRole,
        ImageUrlRole,
        ColorsRole,
        ColorIdentityRole
    };

    explicit CardModel(QObject *parent = nullptr);

    int rowCount(
        const QModelIndex &parent = QModelIndex()
        ) const override;

    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole
        ) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count() const;

    Q_INVOKABLE Card *cardAt(int index) const;

    void setCards(const QList<Card *> &cards);

    void clear();

signals:

    void countChanged();

private:

    QList<Card *> m_cards;
};

#endif // CARDMODEL_H