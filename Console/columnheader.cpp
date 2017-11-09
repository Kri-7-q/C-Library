#include "columnheader.h"

class ColumnHeader::Private {

public:
    Private();
    Private(const Private* other);
    Private(const QString& headerText, const QString& mapKey);
    Private(const QString& headerText, const QString& mapKey, const quint32 width);
    Private(const QString& headerText, const QString& mapKey, const quint32 width, const TextStyle::TextAlign align);

    QString m_headerText;
    QString m_mapKey;
    quint32 m_width;
    TextStyle::TextAlign m_textAlign;
};

/**
 * Standard constructor class Private of TableHeader
 */
ColumnHeader::Private::Private() :
    m_width(0),
    m_textAlign(TextStyle::Left)
{

}

/**
 * Copy constructor
 * @param other
 */
ColumnHeader::Private::Private(const ColumnHeader::Private *other) :
    m_headerText(other->m_headerText),
    m_mapKey(other->m_mapKey),
    m_width(other->m_width),
    m_textAlign(other->m_textAlign)
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
    m_width(0),
    m_textAlign(TextStyle::Left)
{

}

/**
 * Constructor class Private with initial values.
 * @param headerText        The text which is shown as table header.
 * @param mapKey            A key to get the value from QVariantMap.
 * @param width             The width of table column.
 */
ColumnHeader::Private::Private(const QString &headerText, const QString &mapKey, const quint32 width) :
    m_headerText(headerText),
    m_mapKey(mapKey),
    m_width(width),
    m_textAlign(TextStyle::Left)
{

}

/**
 * Constructor class Private with initial values.
 * @param headerText
 * @param mapKey
 * @param width
 * @param align
 */
ColumnHeader::Private::Private(const QString &headerText, const QString &mapKey, const quint32 width, const TextStyle::TextAlign align) :
    m_headerText(headerText),
    m_mapKey(mapKey),
    m_width(width),
    m_textAlign(align)
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
ColumnHeader::ColumnHeader(const QString &headerText, const QString &mapKey, const quint32 width) :
    d(new Private(headerText, mapKey, width))
{

}

/**
 * Constructor class ColumnHeader with initial values.
 * @param headerText
 * @param mapKey
 * @param width
 * @param align
 */
ColumnHeader::ColumnHeader(const QString &headerText, const QString &mapKey, const quint32 width, const TextStyle::TextAlign align) :
    d(new Private(headerText, mapKey, width, align))
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
quint32 ColumnHeader::columnWidth() const
{
    return d->m_width;
}

/**
 * Setter
 * The width of a table column can be set but is not required. If there is
 * no width given it will be found automatically.
 * @param width     The columns width.
 */
void ColumnHeader::setColumnWidth(const quint32 width)
{
    d->m_width = width;
}

/**
 * Getter
 * @return Columns text align.
 */
TextStyle::TextAlign ColumnHeader::textAlign() const
{
    return d->m_textAlign;
}

/**
 * Setter
 * @param align         Columns text align.
 */
void ColumnHeader::setTextAlign(const TextStyle::TextAlign align)
{
    d->m_textAlign = align;
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
