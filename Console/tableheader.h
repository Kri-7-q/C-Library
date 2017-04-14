#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "console_global.h"
#include "columnheader.h"
#include "textattribute.h"

class CONSOLESHARED_EXPORT TableHeader
{
public:
    TableHeader();
    ~TableHeader();

    void addColumn(const QString& headerText, const QString& mapKey, const quint16 width = 0);
    QString headerText(const int column) const;
    void setHeaderText(const int column, const QString& headerText) const;
    QString mapKey(const int column) const;
    void setMapKey(const int column, const QString& mapKey) const;
    quint16 width(const int column) const;
    void setWidth(const int column, const quint16 width) const;
    int totalWidth() const;
    int size() const;
    TextAttribute fondAttribute() const;
    void setFondAttribute(const TextAttribute& fondAttribute);
    void setFondColor(const TextAttribute::Color color);
    void setBackgrColor(const TextAttribute::Color color);

private:
    class Private;
    Private* d;
};

#endif // TABLEHEADER_H
