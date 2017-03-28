#include "columnheader.h"

class ColumnHeader::Private {

public:
    Private();
    Private(const Private* other);
    Private(const QString& headerText, const QString& mapKey);
    Private(const QString& headerText, const QString& mapKey, const quint16 width);

    QString m_headerText;
    QString m_mapKey;
    quint16 m_width;
};

/**
 * Standard constructor class Private of TableHeader
 */
ColumnHeader::Private::Private() :
    m_width(0)
{

}

/**
 * Copy constructor
 * @param other
 */
ColumnHeader::Private::Private(const ColumnHeader::Private *other) :
    m_headerText(other->m_headerText),
    m_mapKey(other->m_mapKey),
    m_width(other->m_width)
{

}

/**
 * Constructor class Private with initial values.
 * @param headerText        The text which is shown as table header.
 * @param mapKey            A key to get the value from QVariantMap.
 */
ColumnHeader::Private::Private(const QString &headerText, const QString &mapKey) :
    m_headerText(headerText),
    m_mapKey(mapKey),
    m_width(0)
{

}

/**
 * Constructor class Private with initial values.
 * @param headerText        The text which is shown as table header.
 * @param mapKey            A key to get the value from QVariantMap.
 * @param width             The width of table column.
 */
ColumnHeader::Private::Private(const QString &headerText, const QString &mapKey, const quint16 width) :
    m_headerText(headerText),
    m_mapKey(mapKey),
    m_width(width)
{

}

// ---------------------------------------------------------------------------------------------------
// TableHeader
// ---------------------------------------------------------------------------------------------------


/**
 * Standard constructor class ColumnHeader.
 */
ColumnHeader::ColumnHeader() :
    d(new Private())
{

}

/**
 * Copy constructor class ColumnHeader.
 * @param other
 */
ColumnHeader::ColumnHeader(const ColumnHeader &other) :
    d(new Private(other.d))
{

}

/**
 * Constructor class ColumnHeader with initial values.
 * @param headerText
 * @param mapKey
 */
ColumnHeader::ColumnHeader(const QString &headerText, const QString &mapKey) :
    d(new Private(headerText, mapKey))
{

}

/**
 * Constructor class ColumnHeader with initial values.
 * @param headerText
 * @param mapKey
 * @param width         The width of table column. Is not required. Will be found automatically
 *                      if is set to 0.
 */
ColumnHeader::ColumnHeader(const QString &headerText, const QString &mapKey, const quint16 width) :
    d(new Private(headerText, mapKey, width))
{

}

/**
 * Destructor class ColumnHeader.
 * Removes the Private object from heap.
 */
ColumnHeader::~ColumnHeader()
{
    delete d;
}

/**
 * Getter
 * @return      The text which is shown as header.
 */
QString ColumnHeader::headerText() const
{
    return d->m_headerText;
}

/**
 * Setter
 * @param headerText    The text which is shown as header.
 */
void ColumnHeader::setHeaderText(const QString &headerText)
{
    d->m_headerText = headerText;
}

/**
 * Getter
 * @return          The key to the value in QVariantMap.
 */
QString ColumnHeader::mapKey() const
{
    return d->m_mapKey;
}

/**
 * Setter
 * @param mapKey
 */
void ColumnHeader::setMapKey(const QString &mapKey)
{
    d->m_mapKey = mapKey;
}

/**
 * Getter
 * @return          The width of the table column.
 */
quint16 ColumnHeader::columnWidth() const
{
    return d->m_width;
}

/**
 * Setter
 * The width of a table column can be set but is not required. If there is
 * no width given it will be found automatically.
 * @param width     The columns width.
 */
void ColumnHeader::setColumnWidth(const quint16 width)
{
    d->m_width = width;
}

/**
 * Operator overload.
 * @param other
 * @return
 */
ColumnHeader &ColumnHeader::operator = (const ColumnHeader &other)
{
    delete d;
    d = new Private(other.d);

    return *this;
}
