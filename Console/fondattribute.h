#ifndef FONDATTRIBUTE_H
#define FONDATTRIBUTE_H

#include "console_global.h"
#include <QString>

class CONSOLESHARED_EXPORT FondAttribute
{
public:   
    enum Effect { NORMAL, BOLD, UNDERLINED = 4 };
    enum Color { BLACK = 30, RED, GREEN, BROWN, BLUE, PURPLE, CYAN, GRAY };
    enum BackgrColor { BG_BLACK = 40, BG_RED, BG_GREEN, BG_BROWN, BG_BLUE, BG_PURPLE, BG_CYAN, BG_GRAY, STANDARD = 49 };

    // Constructor
    FondAttribute();
    FondAttribute(const Color color, const BackgrColor backgrColor = STANDARD, const Effect effect = NORMAL);

    // Getter and Setter
    Color fondColor() const;
    void setFondColor(const Color color);
    BackgrColor backgroundColor() const;
    void setBackgroundColor(const BackgrColor backgrColor);
    Effect fondEffect() const;
    void setFondEffect(const Effect effect);

    // Methods
    QString fondCode() const;
    void toStandard();

    // Static methods
    static QString fondCode(const Color color, const BackgrColor backgrColor, const Effect effect);

    // Operator overload
    FondAttribute& operator = (const FondAttribute& other);

private:
    class Private;
    Private* d;
};

#endif // FONDATTRIBUTE_H
