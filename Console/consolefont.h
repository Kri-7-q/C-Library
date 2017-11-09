#ifndef FONDATTRIBUTE_H
#define FONDATTRIBUTE_H

#include "console_global.h"
#include <QString>

class CONSOLESHARED_EXPORT ConsoleFont
{
public:   
    // Constructor
    ConsoleFont();
    ConsoleFont(const ConsoleFont& other);
    ConsoleFont(const TextStyle::Color color, const TextStyle::Color backgrColor = TextStyle::Standard, const TextStyle::Effect effect = TextStyle::Normal);

    // Getter and Setter
    TextStyle::Color fondColor() const;
    void setFondColor(const TextStyle::Color color);
    TextStyle::Color backgroundColor() const;
    void setBackgroundColor(const TextStyle::Color backgrColor);
    TextStyle::Effect fondEffect() const;
    void setFondEffect(const TextStyle::Effect effect);

    // Methods
    QString fondCode() const;
    void toStandard();

    // Static methods
    static QString fondCode(const TextStyle::Color color, const TextStyle::Color backgrColor, const TextStyle::Effect effect);

    // Operator overload
    ConsoleFont& operator = (const ConsoleFont& other);

private:
    class Private;
    Private* d;
};

#endif // FONDATTRIBUTE_H
