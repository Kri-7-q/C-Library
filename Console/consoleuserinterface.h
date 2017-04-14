#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include "colorbool.h"
#include "textattribute.h"
#include "tableheader.h"
#include <QVariantMap>


class CONSOLESHARED_EXPORT ConsoleUserInterface
{
public:
    ConsoleUserInterface();
    ~ConsoleUserInterface();

    // Getter and Setter
    void setBackgroundColor(const TextAttribute::Color background);
    void setFondColor(const TextAttribute::Color fondColor);
    void setFondEffect(const TextAttribute::Effect effect);
    TextAttribute::Color backgroundColor() const;
    TextAttribute::Color fondColor() const;
    TextAttribute::Effect fondEffect() const;

    // Methods
    void print(const QString& text) const;
    void println(const QString& text) const;
    void printError(const QString& errorMsg) const;
    void printWarning(const QString& warningMsg) const;
    void printSuccess(const QString& successMsg) const;
    void printTable(const QList<QVariantMap>& valueList, const TableHeader &header) const;
    void printTextField(const QString& text, const quint16 width, const TextAttribute::TextAlign align) const;
    void printMap(const QVariantMap& variantMap) const;

    // Operator overload
    ConsoleUserInterface& operator << (const QString& text);
    ConsoleUserInterface& operator << (const TextAttribute::Color fondColor);
    ConsoleUserInterface& operator << (const TextAttribute::Effect effect);
    ConsoleUserInterface& operator << (const int number);
    ConsoleUserInterface& operator << (const char symbol);
    ConsoleUserInterface& operator << (const double number);
    ConsoleUserInterface& operator << (const bool boolean);
    ConsoleUserInterface& operator << (const char* const text);
    ConsoleUserInterface& operator << (const ColorBool& boolean);
    ConsoleUserInterface& operator << (const TextAttribute& fondAttribute);

private:
    class Private;
    Private* d;
};

#endif // CONSOLEUSERINTERFACE_H
