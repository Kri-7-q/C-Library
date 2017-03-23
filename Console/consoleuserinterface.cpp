#include "consoleuserinterface.h"
#include <QTextStream>

/**
 * @brief The ConsoleUserInterface::Private class
 */
class ConsoleUserInterface::Private {

public:
    Private();

    // Functions
    QString fondAttributes(const BackgrColor background, const Color forground, const Effect effect) const;
    void setStandardAttributes();
    QString currentFondAttributes() const;

    // Members
    BackgrColor m_backgroundColor;
    Color m_fondColor;
    Effect m_effect;
    QTextStream m_outStream;
};

/**
 * Standard constructor of class Private.
 */
ConsoleUserInterface::Private::Private() :
    m_backgroundColor(STANDARD),
    m_fondColor(GRAY),
    m_effect(LIGHT),
    m_outStream(stdout)
{

}

/**
 * Get a string which causes the console the change fond attributes.
 * @param background
 * @param forground
 * @param effect
 * @return  A string to configure console.
 */
QString ConsoleUserInterface::Private::fondAttributes(const BackgrColor background, const Color forground, const Effect effect) const
{
    QString code("\033[%1;%2;%3m");

    return code.arg(background).arg(effect).arg(forground);
}

/**
 * Set to standard configuration.
 */
void ConsoleUserInterface::Private::setStandardAttributes()
{
    m_backgroundColor = STANDARD;
    m_fondColor = GRAY;
    m_effect = LIGHT;
    m_outStream << currentFondAttributes();
}

/**
 * Build a configuration string with the current settings to set fond attributes.
 * @return      A string to configure the console with the fond attributes.
 */
QString ConsoleUserInterface::Private::currentFondAttributes() const
{
    QString code("\033[%1;%2;%3m");

    return code.arg(m_backgroundColor).arg(m_fondColor).arg(m_effect);
}

// -------------------------------------------------------------------------------------------------------
// ConsoleUserInterface
// -------------------------------------------------------------------------------------------------------

/**
 * @brief ConsoleUserInterface::ConsoleUserInterface
 */
ConsoleUserInterface::ConsoleUserInterface() :
    d(new Private())
{

}

/**
 * Destructor of class ConsoleUserInterface
 * Removes Private object from heap.
 */
ConsoleUserInterface::~ConsoleUserInterface()
{
    d->m_outStream << "\033[0m";
    delete d;
}

/**
 * Setter
 * @param background
 */
void ConsoleUserInterface::setBackgroundColor(const BackgrColor background)
{
    d->m_backgroundColor = background;
    d->m_outStream << d->currentFondAttributes();
}

/**
 * Setter
 * @param forground
 */
void ConsoleUserInterface::setFondColor(const ConsoleUserInterface::Color fondColor)
{
    d->m_fondColor = fondColor;
    d->m_outStream << d->currentFondAttributes();
}

/**
 * Setter
 * @param effect
 */
void ConsoleUserInterface::setFondEffect(const ConsoleUserInterface::Effect effect)
{
    d->m_effect = effect;
    d->m_outStream << d->currentFondAttributes();
}

/**
 * Getter
 * @return
 */
ConsoleUserInterface::BackgrColor ConsoleUserInterface::backgroundColor() const
{
    return d->m_backgroundColor;
}

/**
 * Getter
 * @return
 */
ConsoleUserInterface::Color ConsoleUserInterface::fondColor() const
{
    return d->m_fondColor;
}

/**
 * Getter
 * @return
 */
ConsoleUserInterface::Effect ConsoleUserInterface::fondEffect() const
{
    return d->m_effect;
}

/**
 * Print a string to the console with the configured fond.
 */
void ConsoleUserInterface::print(const QString &text) const
{
    d->m_outStream << text;
}

/**
 * Print a string to the console with the configured fond.
 * At the end of the text it starts a new line in the console.
 * @param text
 */
void ConsoleUserInterface::println(const QString &text) const
{
    d->m_outStream << text << endl;
}

/**
 * Print an error message in red fond color to the console.
 * @param errorMsg
 */
void ConsoleUserInterface::printError(const QString &errorMsg) const
{
    QString fondAttributes = d->fondAttributes(STANDARD, RED, NORMAL);
    QString setBackFond = d->currentFondAttributes();
    d->m_outStream << fondAttributes << errorMsg << setBackFond << endl;
}

/**
 * Print a warning in brown fond color to the console.
 * @param warningMsg
 */
void ConsoleUserInterface::printWarning(const QString& warningMsg) const
{
    QString fondAttributes = d->fondAttributes(STANDARD, BROWN, NORMAL);
    QString setBackFond = d->currentFondAttributes();
    d->m_outStream << fondAttributes << warningMsg << setBackFond << endl;
}

/**
 * Prints a success message in green fond color to the console.
 * @param successMsg
 */
void ConsoleUserInterface::printSuccess(const QString &successMsg) const
{
    QString fondAttributes = d->fondAttributes(STANDARD, GREEN, NORMAL);
    QString setBackFond = d->currentFondAttributes();
    d->m_outStream << fondAttributes << successMsg << setBackFond << endl;
}

/**
 * Operator overload
 * Print text to the console with the current fond attributes.
 * @param text      Text to print.
 * @return          A reference to the user interface.
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const QString& text)
{
    d->m_outStream << text;

    return *this;
}

/**
 * Set a fond color to the console.
 * @param fondColor
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const ConsoleUserInterface::Color fondColor)
{
    setFondColor(fondColor);

    return *this;
}

/**
 * Set a background color to the console.
 * @param backgrColor
 * @return
 */
ConsoleUserInterface&  ConsoleUserInterface::operator << (const ConsoleUserInterface::BackgrColor backgrColor)
{
    setBackgroundColor(backgrColor);

    return *this;
}

/**
 * Set a fond effect to the console.
 * @param effect
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const ConsoleUserInterface::Effect effect)
{
    setFondEffect(effect);

    return *this;
}

/**
 * Prints a integer to the console in the current configuration.
 * @param number
 * @return
 */
ConsoleUserInterface &ConsoleUserInterface::operator << (const int number)
{
    d->m_outStream << number;

    return *this;
}

/**
 * Prints a char to the console in the current configuration.
 * @param symbol
 * @return
 */
ConsoleUserInterface &ConsoleUserInterface::operator <<(const char symbol)
{
    d->m_outStream << symbol;

    return *this;
}

/**
 * Prints a double to the console in the current configuration.
 * @param number
 * @return
 */
ConsoleUserInterface &ConsoleUserInterface::operator <<(const double number)
{
    d->m_outStream << number;

    return *this;
}

/**
 * Prints a bool to the console in the current configuration.
 * Prints 'true' or 'false' as a string.
 * @param boolean
 * @return
 */
ConsoleUserInterface &ConsoleUserInterface::operator <<(const bool boolean)
{
    QString value = boolean ? QString("true") : QString("false");
    d->m_outStream << value;

    return *this;
}

/**
 * Prints a c-string to the console in the current configuration.
 * @param text
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const char * const text)
{
    d->m_outStream << text;

    return *this;
}

/**
 * Prints a ColorBool to the console. It prints 'true' in green fond color
 * and 'false' in red fond color.
 * @param boolean
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const ColorBool& boolean)
{
    Color color = boolean.m_bool ? GREEN : RED;
    QString fondColor = d->fondAttributes(d->m_backgroundColor, color, d->m_effect);
    QString value = boolean.m_bool ? QString("true") : QString("false");
    d->m_outStream << fondColor << value << d->currentFondAttributes();

    return *this;
}
