#include "tableheader.h"
#include <QList>
#include "Exception/interfaceexception.h"

class TableHeader::Private {
public:
    Private();

    QList<ColumnHeader> m_columnList;
    ConsoleFont m_fondAttribute;
};

/**
 * Standard constructor class Private of TableHeader.
 */
TableHeader::Private::Private() :
    m_fondAttribute(TextStyle::Blue)
{

}

// ---------------------------------------------------------------------------------------------------------------
// Class TableHeader
// ---------------------------------------------------------------------------------------------------------------

/**
 * Standard constructor class TableHeader
 */
TableHeader::TableHeader() :
    d(new Private())
{

}

/**
 * Destructor class TableHeader
 * Removes Private object from heap.
 */
TableHeader::~TableHeader()
{
    delete d;
}

/**
 * Add a column to the TableHeader.
 * @param headerText        The columns header text which is printed.
 * @param mapKey            A key to a QVariantMap value.
 * @param width             Columns width. Is optional and found automatically if not given.
 */
void TableHeader::addColumn(const QString &headerText, const QString &mapKey, const quint16 width, const TextStyle::TextAlign align)
{
    ColumnHeader column(headerText, mapKey, width, align);
    d->m_columnList << column;
}

/**
 * Getter
 * @param column
 * @return
 */
ColumnHeader &TableHeader::column(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("column()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column];
}

/**
 * Getter
 * @param column        The column number of table.
 * @return              The shown text of column header.
 */
QString TableHeader::headerText(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("headerText()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column].headerText();
}

/**
 * Setter
 * Set the header text of a column.
 * @param column            The column where to modify the header text.
 * @param headerText        The text to set.
 */
void TableHeader::setHeaderText(const int column, const QString &headerText) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("setHeaderText()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }
    d->m_columnList[column].setHeaderText(headerText);
}

/**
 * Getter
 * @param column        The column number of table.
 * @return              The key to a QVariantMap object to get the value.
 */
QString TableHeader::mapKey(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("mapKey()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column].mapKey();
}

/**
 * Setter
 * @param column        The column which get a new key for the QVariantMap objects.
 * @param mapKey        The key value.
 */
void TableHeader::setMapKey(const int column, const QString &mapKey) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("setMapKey()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column].setMapKey(mapKey);
}

/**
 * Getter
 * @param column        The column number of table.
 * @return              The width of the column.
 */
quint32 TableHeader::width(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("width()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column].columnWidth();
}

/**
 * Setter
 * @param column        The column of which the width is to modify.
 * @param width         The new width of column.
 */
void TableHeader::setWidth(const int column, const quint32 width) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("setWidth()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }
    d->m_columnList[column].setColumnWidth(width);
}

/**
 * Getter
 * @param column
 * @return
 */
TextStyle::TextAlign TableHeader::columnAlign(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("columnAlign()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }

    return d->m_columnList[column].textAlign();
}

/**
 * Setter
 * @param column
 * @param align
 */
void TableHeader::setColumnAlign(const int column, const TextStyle::TextAlign align)
{
    if (column < 0 || column >= d->m_columnList.size()) {
        throw InterfaceException(QString("TableHeader"),
                                 QString("setColumnAlign()"),
                                 QString("Column number %1 does not exist !").arg(column));
    }
    d->m_columnList[column].setTextAlign(align);
}

/**
 * Getter
 * Get the total width of all columns together.
 * @return          Width of all columns together.
 */
int TableHeader::totalWidth() const
{
    int width = 0;
    for (int index=0; index<d->m_columnList.size(); ++index) {
        width += d->m_columnList[index].columnWidth();
    }

    return width;
}

/**
 * Getter
 * @return          Number of columns in the TableHeader object.
 */
int TableHeader::size() const
{
    return d->m_columnList.size();
}

/**
 * Getter
 * @return
 */
ConsoleFont TableHeader::fondAttribute() const
{
    return d->m_fondAttribute;
}

/**
 * Setter
 * @param fondAttribute
 */
void TableHeader::setFondAttribute(const ConsoleFont &fondAttribute)
{
    d->m_fondAttribute = fondAttribute;
}

/**
 * Setter
 * @param color
 */
void TableHeader::setFondColor(const TextStyle::Color color)
{
    d->m_fondAttribute.setFondColor(color);
}

/**
 * Setter
 * @param color
 */
void TableHeader::setBackgrColor(const TextStyle::Color color)
{
    d->m_fondAttribute.setBackgroundColor(color);
}
