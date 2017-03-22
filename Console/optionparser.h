#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include "optiondefinition.h"
#include <QHash>

typedef QHash<char, QVariant> OptionTable;

class CONSOLESHARED_EXPORT OptionParser
{
public:
    OptionParser(const QList<OptionDefinition>& definitionList, const quint8 requiredFreeParam = 0, const quint8 allowedFreeParam = 0);
    ~OptionParser();

    OptionTable parseParameter(const int argc, const char* const argv[], const int start = 1);
    bool hasError() const;
    QString errorMsg() const;
    quint8 requiredFreeParam() const;
    void setRequiredFreParam(const quint8 numRequiredParam);
    quint8 allowedFreeParam() const;
    void setAllowedFreeParam(const quint8 numAllowedParam);

private:
    class Private;
    Private* d;
};

#endif // OPTIONPARSER_H
