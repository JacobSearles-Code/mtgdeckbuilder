#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QString>
#include <QStringList>

class Card : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString manaCost READ manaCost CONSTANT)
    Q_PROPERTY(QString typeLine READ typeLine CONSTANT)
    Q_PROPERTY(QString oracleText READ oracleText CONSTANT)
    Q_PROPERTY(QString imageUrl READ imageUrl CONSTANT)
    Q_PROPERTY(QStringList colors READ colors CONSTANT)
    Q_PROPERTY(QStringList colorIdentity READ colorIdentity CONSTANT)

public:

    explicit Card(
        const QString &id,
        const QString &name,
        const QString &manaCost,
        const QString &typeLine,
        const QString &oracleText,
        const QString &imageUrl,
        const QStringList &colors,
        const QStringList &colorIdentity,
        QObject *parent = nullptr
        );

    QString id() const;
    QString name() const;
    QString manaCost() const;
    QString typeLine() const;
    QString oracleText() const;
    QString imageUrl() const;
    QStringList colors() const;
    QStringList colorIdentity() const;

private:

    QString m_id;
    QString m_name;
    QString m_manaCost;
    QString m_typeLine;
    QString m_oracleText;
    QString m_imageUrl;
    QStringList m_colors;
    QStringList m_colorIdentity;
};

#endif // CARD_H