#include "textattribute.h"


class TextAttribute::Private {
public:
    Private();
    Private(const Private* other);
    Private(const Color color, const Color backgrColor, const Effect effect);

    void setEqualTo(const Private* const d);

    Color m_fondColor;
    Color m_backgrColor;
    Effect m_effect;
};

/**
 * Standard constructor Private
 */
TextAttribute::Private::Private() :
    m_fondColor(STANDARD),
    m_backgrColor(STANDARD),
    m_effect(NORMAL)
{

}

/**
 * Copy constructor of class Private
 * @param other
 */
TextAttribute::Private::Private(const TextAttribute::Private *other) :
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
TextAttribute::Private::Private(const Color color, const Color backgrColor, const Effect effect) :
    m_fondColor(color),
    m_backgrColor(backgrColor),
    m_effect(effect)
{

}

/**
 * Setter
 * @param d
 */
void TextAttribute::Private::setEqualTo(const TextAttribute::Private * const d)
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
TextAttribute::TextAttribute() :
    d(new Private())
{

}

/**
 * Copy constructor
 * @param other
 */
TextAttribute::TextAttribute(const TextAttribute &other) :
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
TextAttribute::TextAttribute(const TextAttribute::Color color, const TextAttribute::Color backgrColor, const TextAttribute::Effect effect) :
    d(new Private(color, backgrColor, effect))
{

}

/**
 * Getter
 * @return
 */
TextAttribute::Color TextAttribute::fondColor() const
{
    return d->m_fondColor;
}

/**
 * Setter
 * @param color
 */
void TextAttribute::setFondColor(const TextAttribute::Color color)
{
    d->m_fondColor = color;
}

/**
 * Getter
 * @return
 */
TextAttribute::Color TextAttribute::backgroundColor() const
{
    return d->m_backgrColor;
}

/**
 * Setter
 * @param backgrColor
 */
void TextAttribute::setBackgroundColor(const Color backgrColor)
{
    d->m_backgrColor = backgrColor;
}

/**
 * Getter
 * @return
 */
TextAttribute::Effect TextAttribute::fondEffect() const
{
    return d->m_effect;
}

/**
 * Setter
 * @param effect
 */
void TextAttribute::setFondEffect(const TextAttribute::Effect effect)
{
    d->m_effect = effect;
}

/**
 * Get a string with the fond code which can be parsed from the console to configure fond.
 * @return
 */
QString TextAttribute::fondCode() const
{
    QString code;
    if (d->m_effect == NORMAL) {
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
void TextAttribute::toStandard()
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
QString TextAttribute::fondCode(const TextAttribute::Color color, const Color backgrColor, const TextAttribute::Effect effect)
{
    TextAttribute attribute(color, backgrColor, effect);

    return attribute.fondCode();
}

/**
 * Operator overload
 * Assignment operator overload.
 * @param other         The FondAttribute object to assign to this.
 * @return
 */
TextAttribute& TextAttribute::operator = (const TextAttribute& other)
{
    d->setEqualTo(other.d);

    return *this;
}