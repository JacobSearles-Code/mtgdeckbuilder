#include "Card.h"

Card::Card(
    const QString &id,
    const QString &name,
    const QString &manaCost,
    const QString &typeLine,
    const QString &oracleText,
    const QString &imageUrl,
    const QStringList &colors,
    const QStringList &colorIdentity,
    QObject *parent
    )
    : QObject(parent),
    m_id(id),
    m_name(name),
    m_manaCost(manaCost),
    m_typeLine(typeLine),
    m_oracleText(oracleText),
    m_imageUrl(imageUrl),
    m_colors(colors),
    m_colorIdentity(colorIdentity)
{
}

QString Card::id() const
{
    return m_id;
}

QString Card::name() const
{
    return m_name;
}

QString Card::manaCost() const
{
    return m_manaCost;
}

QString Card::typeLine() const
{
    return m_typeLine;
}

QString Card::oracleText() const
{
    return m_oracleText;
}

QString Card::imageUrl() const
{
    return m_imageUrl;
}

QStringList Card::colors() const
{
    return m_colors;
}

QStringList Card::colorIdentity() const
{
    return m_colorIdentity;
}