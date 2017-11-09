#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "console_global.h"
#include "columnheader.h"
#include "consolefont.h"

class CONSOLESHARED_EXPORT TableHeader
{
public:
    TableHeader();
    ~TableHeader();

    void addColumn(const QString& headerText, const QString& mapKey, const quint16 width = 0, const TextStyle::TextAlign align = TextStyle::Left);
    ColumnHeader& column(const int column) const;
    QString headerText(const int column) const;
    void setHeaderText(const int column, const QString& headerText) const;
    QString mapKey(const int column) const;
    void setMapKey(const int column, const QString& mapKey) const;
    quint32 width(const int column) const;
    void setWidth(const int column, const quint32 width) const;
    TextStyle::TextAlign columnAlign(const int column) const;
    void setColumnAlign(const int column, const TextStyle::TextAlign align);
    int totalWidth() const;
    int size() const;
    ConsoleFont fondAttribute() const;
    void setFondAttribute(const ConsoleFont& fondAttribute);
    void setFondColor(const TextStyle::Color color);
    void setBackgrColor(const TextStyle::Color color);

private:
    class Private;
    Private* d;
};

#endif // TABLEHEADER_H
