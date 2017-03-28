#include "tableheader.h"
#include <QList>

class TableHeader::Private {
public:
    QList<ColumnHeader> m_columnList;
};

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
void TableHeader::addColumn(const QString &headerText, const QString &mapKey, const quint16 width)
{
    ColumnHeader column(headerText, mapKey, width);
    d->m_columnList << column;
}

/**
 * Getter
 * @param column        The column number of table.
 * @return              The shown text of column header.
 */
QString TableHeader::headerText(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        return QString();
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
        return;
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
        return QString();
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
        return;
    }

    return d->m_columnList[column].setMapKey(mapKey);
}

/**
 * Getter
 * @param column        The column number of table.
 * @return              The width of the column.
 */
quint16 TableHeader::width(const int column) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        return 0;
    }

    return d->m_columnList[column].columnWidth();
}

/**
 * Setter
 * @param column        The column of which the width is to modify.
 * @param width         The new width of column.
 */
void TableHeader::setWidth(const int column, const quint16 width) const
{
    if (column < 0 || column >= d->m_columnList.size()) {
        return;
    }
    d->m_columnList[column].setColumnWidth(width);
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
