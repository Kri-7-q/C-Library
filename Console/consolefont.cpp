#include "consolefont.h"


class ConsoleFont::Private {
public:
    Private();
    Private(const Private* other);
    Private(const TextStyle::Color color, const TextStyle::Color backgrColor, const TextStyle::Effect effect);

    void setEqualTo(const Private* const d);

    TextStyle::Color m_fondColor;
    TextStyle::Color m_backgrColor;
    TextStyle::Effect m_effect;
};

/**
 * Standard constructor Private
 */
ConsoleFont::Private::Private() :
    m_fondColor(TextStyle::Standard),
    m_backgrColor(TextStyle::Standard),
    m_effect(TextStyle::Normal)
{

}

/**
 * Copy constructor of class Private
 * @param other
 */
ConsoleFont::Private::Private(const ConsoleFont::Private *other) :
    m_fondColor(other->m_fondColor),
    m_backgrColor(other->m_backgrColor),
    m_effect(other->m_effect)
{

}

/**
 * Constructor class Private
 * Creates a fully initialized Private object.
 * @param color
 * @param backgrColor
 * @param effect
 */
ConsoleFont::Private::Private(const TextStyle::Color color, const TextStyle::Color backgrColor, const TextStyle::Effect effect) :
    m_fondColor(color),
    m_backgrColor(backgrColor),
    m_effect(effect)
{

}

/**
 * Setter
 * @param d
 */
void ConsoleFont::Private::setEqualTo(const ConsoleFont::Private * const d)
{
    m_fondColor = d->m_fondColor;
    m_backgrColor = d->m_backgrColor;
    m_effect = d->m_effect;
}

// -------------------------------------------------------------------------------------------------------------
// Class FondAttribute
// -------------------------------------------------------------------------------------------------------------

/**
 * Standard constructor FondAttribute
 */
ConsoleFont::ConsoleFont() :
    d(new Private())
{

}

/**
 * Copy constructor
 * @param other
 */
ConsoleFont::ConsoleFont(const ConsoleFont &other) :
    d(new Private(other.d))
{

}

/**
 * Constructor class FondAttribute
 * Creates a fully initialized FondAttribute obect.
 * @param color             Fond color.
 * @param backgrColor       Fond background color.
 * @param effect            Fond effect.
 */
ConsoleFont::ConsoleFont(const TextStyle::Color color, const TextStyle::Color backgrColor, const TextStyle::Effect effect) :
    d(new Private(color, backgrColor, effect))
{

}

/**
 * Getter
 * @return
 */
TextStyle::Color ConsoleFont::fondColor() const
{
    return d->m_fondColor;
}

/**
 * Setter
 * @param color
 */
void ConsoleFont::setFondColor(const TextStyle::Color color)
{
    d->m_fondColor = color;
}

/**
 * Getter
 * @return
 */
TextStyle::Color ConsoleFont::backgroundColor() const
{
    return d->m_backgrColor;
}

/**
 * Setter
 * @param backgrColor
 */
void ConsoleFont::setBackgroundColor(const TextStyle::Color backgrColor)
{
    d->m_backgrColor = backgrColor;
}

/**
 * Getter
 * @return
 */
TextStyle::Effect ConsoleFont::fondEffect() const
{
    return d->m_effect;
}

/**
 * Setter
 * @param effect
 */
void ConsoleFont::setFondEffect(const TextStyle::Effect effect)
{
    d->m_effect = effect;
}

/**
 * Get a string with the fond code which can be parsed from the console to configure fond.
 * @return
 */
QString ConsoleFont::fondCode() const
{
    QString code;
    if (d->m_effect == TextStyle::Normal) {
        QString pattern("\033[%1;%2m");
        code = pattern.arg(d->m_backgrColor + 10).arg(d->m_fondColor);
    } else {
        QString pattern("\033[%1;%2;%3m");
        code = pattern.arg(d->m_backgrColor + 10).arg(d->m_effect).arg(d->m_fondColor);
    }

    return code;
}

/**
 * Set this FondAttribute object to standard values.
 */
void ConsoleFont::toStandard()
{
    Private val;
    d->setEqualTo(&val);
}

/**
 * Static
 * Get a string with the fond code which can be parsed from the console to configure fond.
 * @param color
 * @param backgrColor
 * @param effect
 * @return
 */
QString ConsoleFont::fondCode(const TextStyle::Color color, const TextStyle::Color backgrColor, const TextStyle::Effect effect)
{
    ConsoleFont attribute(color, backgrColor, effect);

    return attribute.fondCode();
}

/**
 * Operator overload
 * Assignment operator overload.
 * @param other         The FondAttribute object to assign to this.
 * @return
 */
ConsoleFont& ConsoleFont::operator = (const ConsoleFont& other)
{
    d->setEqualTo(other.d);

    return *this;
}
