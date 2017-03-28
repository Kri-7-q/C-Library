#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include "colorbool.h"
#include "fondattribute.h"
#include "tableheader.h"
#include <QVariantMap>


class CONSOLESHARED_EXPORT ConsoleUserInterface
{
public:
    ConsoleUserInterface();
    ~ConsoleUserInterface();

    // Getter and Setter
    void setBackgroundColor(const FondAttribute::BackgrColor background);
    void setFondColor(const FondAttribute::Color fondColor);
    void setFondEffect(const FondAttribute::Effect effect);
    FondAttribute::BackgrColor backgroundColor() const;
    FondAttribute::Color fondColor() const;
    FondAttribute::Effect fondEffect() const;

    // Methods
    void print(const QString& text) const;
    void println(const QString& text) const;
    void printError(const QString& errorMsg) const;
    void printWarning(const QString& warningMsg) const;
    void printSuccess(const QString& successMsg) const;
    void printTable(const QList<QVariantMap>& valueList, const TableHeader &header) const;

    // Operator overload
    ConsoleUserInterface& operator << (const QString& text);
    ConsoleUserInterface& operator << (const FondAttribute::Color fondColor);
    ConsoleUserInterface& operator << (const FondAttribute::BackgrColor backgrColor);
    ConsoleUserInterface& operator << (const FondAttribute::Effect effect);
    ConsoleUserInterface& operator << (const int number);
    ConsoleUserInterface& operator << (const char symbol);
    ConsoleUserInterface& operator << (const double number);
    ConsoleUserInterface& operator << (const bool boolean);
    ConsoleUserInterface& operator << (const char* const text);
    ConsoleUserInterface& operator << (const ColorBool& boolean);
    ConsoleUserInterface& operator << (const FondAttribute& fondAttribute);

private:
    class Private;
    Private* d;
};

#endif // CONSOLEUSERINTERFACE_H
