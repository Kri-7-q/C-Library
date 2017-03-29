#include "consoleuserinterface.h"
#include <QTextStream>

/**
 * @brief The ConsoleUserInterface::Private class
 */
class ConsoleUserInterface::Private {

public:
    Private();

    // Functions
    void setTableColumnWidth(const QList<QVariantMap>& valueList, TableHeader& header) const;
    void printTableHeader(const TableHeader &tableHeader);
    QString tableFieldString(const QString& text, const quint16 width) const;
    QString tableLine(const QVariantMap& valueMap, const TableHeader& header) const;
    inline QString frameLine(const TableHeader& header) const;

    // Members
    FondAttribute m_fondAttribute;
    QTextStream m_outStream;

private:
    quint16 tableColumnWidth(const QList<QVariantMap>& valueList, const QString& key) const;
};

/**
 * Standard constructor of class Private.
 */
ConsoleUserInterface::Private::Private() :
    m_outStream(stdout)
{

}

/**
 * Find the required width of the table columns from values.
 * @param valueList             A list of QVariantMap objects with the contant of the table.
 * @param attributeList         The header objects of the table.
 */
void ConsoleUserInterface::Private::setTableColumnWidth(const QList<QVariantMap> &valueList, TableHeader &header) const
{
    for (quint16 index=0; index<header.size(); ++index) {
        if (header.width(index) > 0) {
            continue;
        }
        quint16 width = tableColumnWidth(valueList, header.mapKey(index));
        header.setWidth(index, width);
    }
}

/**
 * Print the header of a table.
 * @param tableHeader
 */
void ConsoleUserInterface::Private::printTableHeader(const TableHeader& tableHeader)
{
    QString line = frameLine(tableHeader);
    QString header("|");
    for (int index=0; index<tableHeader.size(); ++index) {
        QString field = tableFieldString(tableHeader.headerText(index), tableHeader.width(index));
        header.append(' ').append(field).append(" |");
    }
    QString standardFond = FondAttribute().fondCode();
    QString headerFond = tableHeader.fondAttribute().fondCode();
    m_outStream << headerFond << line << standardFond << endl;
    m_outStream << headerFond << header << standardFond << endl;
    m_outStream << headerFond << line << standardFond << endl;
}

/**
 * Format the text to a table field.
 * If text is longer than the field width then the text will be cut to width.
 * Otherwise the text string is filled with space to get the field width.
 * @param text      The field text.
 * @param width     The field width.
 * @return          A string which represent a table field.
 */
QString ConsoleUserInterface::Private::tableFieldString(const QString &text, const quint16 width) const
{
    if (text.length() >= width) {
        return text.left(width);
    }
    QString space(width - text.length(), ' ');

    return QString(text).append(space);
}

/**
 * Get a line of table view as a string.
 * @param valueMap      The value map which contains all values of a line.
 * @param header        A table header object.
 * @return              A printable string containing all values in fields.
 */
QString ConsoleUserInterface::Private::tableLine(const QVariantMap &valueMap, const TableHeader &header) const
{
    QString line("|");
    for (int index=0; index<header.size(); ++index) {
        QString key = header.mapKey(index);
        QString value = valueMap.value(key, QVariant()).toString();
        QString field = tableFieldString(value, header.width(index));
        line.append(' ').append(field).append(" |");
    }

    return line;
}

/**
 * Get a printable horizontal table frame line string.
 * @param header
 * @return
 */
QString ConsoleUserInterface::Private::frameLine(const TableHeader &header) const
{
    int width = 2 + 2 * header.size() + header.totalWidth() + 3;

    return QString(width, '-');
}

/**
 * Get the width of a table column.
 * Find the max length of values in the list.
 * @param valueList
 * @param key
 * @return
 */
quint16 ConsoleUserInterface::Private::tableColumnWidth(const QList<QVariantMap> &valueList, const QString &key) const
{
    quint16 width = 0;
    for (int index=0; index<valueList.size(); ++index) {
        const QVariantMap& valueMap = valueList[index];
        QVariant value = valueMap[key];
        quint16 length = static_cast<quint16>(value.toString().length());
        if (width < length) {
            width = length;
        }
    }

    return width;
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
void ConsoleUserInterface::setBackgroundColor(const FondAttribute::Color background)
{
    d->m_fondAttribute.setBackgroundColor(background);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Setter
 * @param forground
 */
void ConsoleUserInterface::setFondColor(const FondAttribute::Color fondColor)
{
    d->m_fondAttribute.setFondColor(fondColor);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Setter
 * @param effect
 */
void ConsoleUserInterface::setFondEffect(const FondAttribute::Effect effect)
{
    d->m_fondAttribute.setFondEffect(effect);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Getter
 * @return
 */
FondAttribute::Color ConsoleUserInterface::backgroundColor() const
{
    return d->m_fondAttribute.backgroundColor();
}

/**
 * Getter
 * @return
 */
FondAttribute::Color ConsoleUserInterface::fondColor() const
{
    return d->m_fondAttribute.fondColor();
}

/**
 * Getter
 * @return
 */
FondAttribute::Effect ConsoleUserInterface::fondEffect() const
{
    return d->m_fondAttribute.fondEffect();
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
    QString fondAttributes = FondAttribute::fondCode(FondAttribute::RED, FondAttribute::STANDARD, FondAttribute::NORMAL);
    d->m_outStream << fondAttributes << errorMsg << d->m_fondAttribute.fondCode() << endl;
}

/**
 * Print a warning in brown fond color to the console.
 * @param warningMsg
 */
void ConsoleUserInterface::printWarning(const QString& warningMsg) const
{
    QString fondAttributes = FondAttribute::fondCode(FondAttribute::BROWN, FondAttribute::STANDARD, FondAttribute::NORMAL);
    d->m_outStream << fondAttributes << warningMsg << d->m_fondAttribute.fondCode() << endl;
}

/**
 * Prints a success message in green fond color to the console.
 * @param successMsg
 */
void ConsoleUserInterface::printSuccess(const QString &successMsg) const
{
    QString fondAttributes = FondAttribute::fondCode(FondAttribute::GREEN, FondAttribute::STANDARD, FondAttribute::NORMAL);
    d->m_outStream << fondAttributes << successMsg << d->m_fondAttribute.fondCode() << endl;
}

/**
 * Print a table to the console.
 * Takes a attribute list with the key value of the QVariantMap objects.
 * @param valueList
 * @param attributeList
 */
void ConsoleUserInterface::printTable(const QList<QVariantMap> &valueList, const TableHeader& header) const
{
    d->setTableColumnWidth(valueList, const_cast<TableHeader&>(header));
    d->printTableHeader(header);
    for (int index=0; index<valueList.size(); ++index) {
        d->m_outStream << d->tableLine(valueList[index], header) << endl;;
    }
    d->m_outStream << d->frameLine(header) << endl;
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
ConsoleUserInterface& ConsoleUserInterface::operator << (const FondAttribute::Color fondColor)
{
    setFondColor(fondColor);

    return *this;
}

/**
 * Set a fond effect to the console.
 * @param effect
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const FondAttribute::Effect effect)
{
    setFondEffect(effect);

    return *this;
}

/**
 * Prints a integer to the console in the current configuration.
 * @param number
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const int number)
{
    d->m_outStream << number;

    return *this;
}

/**
 * Prints a char to the console in the current configuration.
 * @param symbol
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const char symbol)
{
    d->m_outStream << symbol;

    return *this;
}

/**
 * Prints a double to the console in the current configuration.
 * @param number
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const double number)
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
ConsoleUserInterface& ConsoleUserInterface::operator << (const bool boolean)
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
    QString color = FondAttribute::fondCode(FondAttribute::RED, FondAttribute::STANDARD, FondAttribute::NORMAL);
    QString value("false");
    if (boolean == true) {
        color = FondAttribute::fondCode(FondAttribute::GREEN, FondAttribute::STANDARD, FondAttribute::NORMAL);
        value = QString("true");
    }
    d->m_outStream << color << value << d->m_fondAttribute.fondCode();

    return *this;
}

/**
 * Prints following text with the given fond attributes.
 * @param fondAttribute         Attributes to configure console fond.
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const FondAttribute& fondAttribute)
{
    d->m_outStream << fondAttribute.fondCode();

    return *this;
}
