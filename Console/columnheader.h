#ifndef COLUMNHEADER_H
#define COLUMNHEADER_H

#include <QString>

class ColumnHeader
{
public:
    ColumnHeader();
    ColumnHeader(const ColumnHeader& other);
    ColumnHeader(const QString& headerText, const QString& mapKey);
    ColumnHeader(const QString& headerText, const QString& mapKey, const quint16 width);
    ~ColumnHeader();

    // Getter and Setter
    QString headerText() const;
    void setHeaderText(const QString& headerText);
    QString mapKey() const;
    void setMapKey(const QString& mapKey);
    quint16 columnWidth() const;
    void setColumnWidth(const quint16 width);

    // Operator overload
    ColumnHeader& operator = (const ColumnHeader& other);

private:
    class Private;
    Private* d;
};

#endif // COLUMNHEADER_H
