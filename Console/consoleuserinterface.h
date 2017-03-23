#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include "console_global.h"
#include <QString>

class CONSOLESHARED_EXPORT ColorBool {
public:
    ColorBool(const bool boolean) :
        m_bool(boolean)
    { }

    bool m_bool;
};

class CONSOLESHARED_EXPORT ConsoleUserInterface
{
public:
    ConsoleUserInterface();
    ~ConsoleUserInterface();

    enum Effect { NORMAL, LIGHT, UNDERLINED = 4 };
    enum Color { BLACK = 30, RED, GREEN, BROWN, BLUE, PURPLE, CYAN, GRAY };
    enum BackgrColor { BG_BLACK = 40, BG_RED, BG_GREEN, BG_BROWN, BG_BLUE, BG_PURPLE, BG_CYAN, BG_GRAY, STANDARD = 49 };

    // Getter and Setter
    void setBackgroundColor(const BackgrColor background);
    void setFondColor(const Color fondColor);
    void setFondEffect(const Effect effect);
    BackgrColor backgroundColor() const;
    Color fondColor() const;
    Effect fondEffect() const;

    // Methods
    void print(const QString& text) const;
    void println(const QString& text) const;
    void printError(const QString& errorMsg) const;
    void printWarning(const QString& warningMsg) const;
    void printSuccess(const QString& successMsg) const;

    // Operator overload
    ConsoleUserInterface& operator << (const QString& text);
    ConsoleUserInterface& operator << (const Color fondColor);
    ConsoleUserInterface& operator << (const BackgrColor backgrColor);
    ConsoleUserInterface& operator << (const Effect effect);
    ConsoleUserInterface& operator << (const int number);
    ConsoleUserInterface& operator << (const char symbol);
    ConsoleUserInterface& operator << (const double number);
    ConsoleUserInterface& operator << (const bool boolean);
    ConsoleUserInterface& operator << (const char* const text);
    ConsoleUserInterface& operator << (const ColorBool& boolean);

private:
    class Private;
    Private* d;
};

#endif // CONSOLEUSERINTERFACE_H
