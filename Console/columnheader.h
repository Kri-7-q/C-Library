#ifndef COLUMNHEADER_H
#define COLUMNHEADER_H

#include "console_global.h"
#include <QString>

class CONSOLESHARED_EXPORT ColumnHeader
{
public:
    ColumnHeader();
    ColumnHeader(const ColumnHeader& other);
    ColumnHeader(const QString& headerText, const QString& mapKey);
    ColumnHeader(const QString& headerText, const QString& mapKey, const quint32 width);
    ColumnHeader(const QString& headerText, const QString& mapKey, const quint32 width, const TextStyle::TextAlign align);
    ~ColumnHeader();

    // Getter and Setter
    QString headerText() const;
    void setHeaderText(const QString& headerText);
    QString mapKey() const;
    void setMapKey(const QString& mapKey);
    quint32 columnWidth() const;
    void setColumnWidth(const quint32 width);
    TextStyle::TextAlign textAlign() const;
    void setTextAlign(const TextStyle::TextAlign align);

    // Operator overload
    ColumnHeader& operator = (const ColumnHeader& other);

private:
    class Private;
    Private* d;
};

#endif // COLUMNHEADER_H
