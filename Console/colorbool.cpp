#include "colorbool.h"

/**
 * Standard constructor of ColorBool
 * A ColorBool created with the standard constructor is allways
 * initialize with the value 'false'.
 */
ColorBool::ColorBool() :
    m_bool(false)
{

}

/**
 * Constructor of ColorBool
 * Creates and initializes a ColorBool object.
 * @param boolean       The initial value of ColorBool.
 */
ColorBool::ColorBool(const bool boolean) :
    m_bool(boolean)
{

}

/**
 * Operator override
 * Overrides the comparison operator to comare two ColorBool objects.
 * @param other     The other ColorBool object which is to compare with this one.
 * @return          True if value of both objects is equal.
 */
bool ColorBool::operator == (const ColorBool& other) const
{
    return m_bool == other.m_bool;
}

/**
 * Operator override
 * Overrides the comparison operator to compare this object with a bool value.
 * @param boolean       Bool value to compare with this ColorBool object.
 * @return
 */
bool ColorBool::operator == (const bool boolean) const
{
    return m_bool == boolean;
}

/**
 * @brief ColorBool::operator =
 * @param other
 */
void ColorBool::operator = (const ColorBool& other)
{
    m_bool = other.m_bool;
}

/**
 * @brief ColorBool::operator =
 * @param boolean
 */
void ColorBool::operator =(const bool boolean)
{
    m_bool = boolean;
}
