#ifndef FONDATTRIBUTE_H
#define FONDATTRIBUTE_H

#include "console_global.h"
#include <QString>

class CONSOLESHARED_EXPORT FondAttribute
{
public:   
    enum Effect { NORMAL, BOLD, ITALIC, UNDERLINED = 4, BLINKING, INVERSE = 7 };
    enum Color { BLACK = 30, RED, GREEN, BROWN, BLUE, PURPLE, CYAN, GRAY, STANDARD = 39 };

    // Constructor
    FondAttribute();
    FondAttribute(const FondAttribute& other);
    FondAttribute(const Color color, const Color backgrColor = STANDARD, const Effect effect = NORMAL);

    // Getter and Setter
    Color fondColor() const;
    void setFondColor(const Color color);
    Color backgroundColor() const;
    void setBackgroundColor(const Color backgrColor);
    Effect fondEffect() const;
    void setFondEffect(const Effect effect);

    // Methods
    QString fondCode() const;
    void toStandard();

    // Static methods
    static QString fondCode(const Color color, const Color backgrColor, const Effect effect);

    // Operator overload
    FondAttribute& operator = (const FondAttribute& other);

private:
    class Private;
    Private* d;
};

#endif // FONDATTRIBUTE_H
