#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include "colorbool.h"
#include "consolefont.h"
#include "tableheader.h"
#include <QVariantMap>


class CONSOLESHARED_EXPORT ConsoleUserInterface
{
public:
    ConsoleUserInterface();
    ~ConsoleUserInterface();

    // Getter and Setter
    void setBackgroundColor(const TextStyle::Color background);
    void setFondColor(const TextStyle::Color fondColor);
    void setFondEffect(const TextStyle::Effect effect);
    TextStyle::Color backgroundColor() const;
    TextStyle::Color fondColor() const;
    TextStyle::Effect fondEffect() const;
    ConsoleFont& fontColorBoolTrue() const;
    ConsoleFont& fontColorBoolFalse() const;

    // Methods
    void print(const QString& text) const;
    void println(const QString& text) const;
    void printError(const QString& errorMsg) const;
    void printWarning(const QString& warningMsg) const;
    void printSuccess(const QString& successMsg) const;
    void printTable(const QList<QVariantMap>& valueList, const TableHeader &header) const;
    void printTextField(const QString& text, const quint16 width, const TextStyle::TextAlign align) const;
    void printMap(const QVariantMap& variantMap) const;

    // Operator overload
    ConsoleUserInterface& operator << (const QString& text);
    ConsoleUserInterface& operator << (const TextStyle::Color fondColor);
    ConsoleUserInterface& operator << (const TextStyle::Effect effect);
    ConsoleUserInterface& operator << (const int number);
    ConsoleUserInterface& operator << (const char symbol);
    ConsoleUserInterface& operator << (const double number);
    ConsoleUserInterface& operator << (const bool boolean);
    ConsoleUserInterface& operator << (const char* const text);
    ConsoleUserInterface& operator << (const ColorBool& boolean);
    ConsoleUserInterface& operator << (const ConsoleFont& fondAttribute);

private:
    class Private;
    Private* d;
};

#endif // CONSOLEUSERINTERFACE_H
