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
    QString textFieldString(const QString& text, const quint16 width, const TextAttribute::TextAlign align = TextAttribute::LEFT) const;
    QString tableLine(const QVariantMap& valueMap, const TableHeader& header) const;
    inline QString frameLine(const TableHeader& header) const;
    quint16 columnWidthOf(const QStringList& list) const;
    quint16 columnWidthOf(const QVariantList& list) const;

    // Members
    TextAttribute m_fondAttribute;
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
        QString field = textFieldString(tableHeader.headerText(index), tableHeader.width(index));
        header.append(' ').append(field).append(" |");
    }
    QString standardFond = TextAttribute().fondCode();
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
QString ConsoleUserInterface::Private::textFieldString(const QString &text, const quint16 width, const TextAttribute::TextAlign align) const
{
    if (width < 1) {
        return QString();
    }
    if (text.length() >= width) {
        return text.left(width);
    }
    int numSpace = width - text.length();
    QString space(numSpace, ' ');
    QString textField(text);
    switch (align) {
    case TextAttribute::LEFT:
        textField.append(space);
        break;
    case TextAttribute::CENTER: {
        int leftSpace = numSpace / 2;
        int rightSpace = leftSpace + numSpace % 2;
        textField = QString(leftSpace, ' ').append(textField).append(QString(rightSpace, ' '));
        break;
    }
    case TextAttribute::RIGTH:
        textField = space.append(textField);
        break;
    }

    return textField;
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
        QString field = textFieldString(value, header.width(index));
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
 * Find the width of column by searching the list for the longest entry.
 * @param list
 * @return
 */
quint16 ConsoleUserInterface::Private::columnWidthOf(const QStringList &list) const
{
    quint16 max = 0;
    foreach (QString item, list) {
        if (item.length() > max) {
            max = static_cast<quint16>(item.length());
        }
    }

    return max;
}

/**
 * Find the width of column by searching the list for the longest entry.
 * QVariant values are converted to string to get the length of longest
 * item in the list.
 * @param list
 * @return
 */
quint16 ConsoleUserInterface::Private::columnWidthOf(const QVariantList &list) const
{
    quint16 max = 0;
    foreach (QVariant item, list) {
        int length = item.toString().length();
        if (length > max) {
            max = static_cast<quint16>(length);
        }
    }

    return max;
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
void ConsoleUserInterface::setBackgroundColor(const TextAttribute::Color background)
{
    d->m_fondAttribute.setBackgroundColor(background);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Setter
 * @param forground
 */
void ConsoleUserInterface::setFondColor(const TextAttribute::Color fondColor)
{
    d->m_fondAttribute.setFondColor(fondColor);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Setter
 * @param effect
 */
void ConsoleUserInterface::setFondEffect(const TextAttribute::Effect effect)
{
    d->m_fondAttribute.setFondEffect(effect);
    d->m_outStream << d->m_fondAttribute.fondCode();
}

/**
 * Getter
 * @return
 */
TextAttribute::Color ConsoleUserInterface::backgroundColor() const
{
    return d->m_fondAttribute.backgroundColor();
}

/**
 * Getter
 * @return
 */
TextAttribute::Color ConsoleUserInterface::fondColor() const
{
    return d->m_fondAttribute.fondColor();
}

/**
 * Getter
 * @return
 */
TextAttribute::Effect ConsoleUserInterface::fondEffect() const
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
    QString fondAttributes = TextAttribute::fondCode(TextAttribute::RED, TextAttribute::STANDARD, TextAttribute::NORMAL);
    d->m_outStream << fondAttributes << errorMsg << d->m_fondAttribute.fondCode() << endl;
}

/**
 * Print a warning in brown fond color to the console.
 * @param warningMsg
 */
void ConsoleUserInterface::printWarning(const QString& warningMsg) const
{
    QString fondAttributes = TextAttribute::fondCode(TextAttribute::BROWN, TextAttribute::STANDARD, TextAttribute::NORMAL);
    d->m_outStream << fondAttributes << warningMsg << d->m_fondAttribute.fondCode() << endl;
}

/**
 * Prints a success message in green fond color to the console.
 * @param successMsg
 */
void ConsoleUserInterface::printSuccess(const QString &successMsg) const
{
    QString fondAttributes = TextAttribute::fondCode(TextAttribute::GREEN, TextAttribute::STANDARD, TextAttribute::NORMAL);
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
 * Print a text field with a given width to the console.
 * The text alignment can be choosen.
 * @param text
 * @param width
 * @param align
 */
void ConsoleUserInterface::printTextField(const QString &text, const quint16 width, const TextAttribute::TextAlign align) const
{
    d->m_outStream << d->textFieldString(text, width, align);
}

/**
 * Print a QVariantMap to the console.
 * Print the key in blue and left aligned. The value is shown in standard color
 * and the text is rigth aligned.
 * @param variantMap
 */
void ConsoleUserInterface::printMap(const QVariantMap &variantMap) const
{
    QStringList keyList = variantMap.keys();
    quint16 headerWidth = d->columnWidthOf(keyList);
    quint16 valueWidth = d->columnWidthOf(variantMap.values());
    QString colorBlue = TextAttribute::fondCode(TextAttribute::BLUE, TextAttribute::STANDARD, TextAttribute::NORMAL);
    QString standard = d->m_fondAttribute.fondCode();
    foreach (QString key, keyList) {
        d->m_outStream << colorBlue << d->textFieldString(key + ':', headerWidth+2, TextAttribute::LEFT) << standard;
        QString val = variantMap.value(key).toString();
        d->m_outStream << d->textFieldString(val, valueWidth, TextAttribute::RIGTH) << endl;
    }
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
ConsoleUserInterface& ConsoleUserInterface::operator << (const TextAttribute::Color fondColor)
{
    setFondColor(fondColor);

    return *this;
}

/**
 * Set a fond effect to the console.
 * @param effect
 * @return
 */
ConsoleUserInterface& ConsoleUserInterface::operator << (const TextAttribute::Effect effect)
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
    QString color = TextAttribute::fondCode(TextAttribute::RED, TextAttribute::STANDARD, TextAttribute::NORMAL);
    QString value("false");
    if (boolean == true) {
        color = TextAttribute::fondCode(TextAttribute::GREEN, TextAttribute::STANDARD, TextAttribute::NORMAL);
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
ConsoleUserInterface& ConsoleUserInterface::operator << (const TextAttribute& fondAttribute)
{
    d->m_outStream << fondAttribute.fondCode();

    return *this;
}
