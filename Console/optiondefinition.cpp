#include "optiondefinition.h"


/**
 * Private
 * Class Private
 * Private implementation of class OptionDefinition
 */
class OptionDefinition::Private {

public:
    Private();
    Private(const char option, const OptionType optionArgument, const QVariant::Type dataType,
            const QString &formatString, const QString &longOption);
    Private(const char option, bool *pSwitch, const QString &longOption);
    Private(Private *rhs);

    char m_option;
    OptionType m_optionType;
    QVariant::Type m_dataType;
    QString m_formatString;
    QString m_longOption;
    bool* m_pSwitch;
};

/**
 * Default constructor of class Private.
 * Constructs a invalid OptionDefinition object.
 * @param parent    The OptionDefinition object which owns this Private object.
 */
OptionDefinition::Private::Private() :
    m_option(0),
    m_optionType(InvalidDefinition),
    m_dataType(QVariant::Invalid),
    m_pSwitch(NULL)
{

}

/**
 * Creates a initialized OptionDefinition object.
 * @param parent                The OptionDefinition object which owns this Private object.
 * @param option
 * @param optionArgument
 * @param dataType
 * @param formatString
 * @param longOption
 */
OptionDefinition::Private::Private(const char option, const OptionType optionArgument,
                                   const QVariant::Type dataType, const QString &formatString, const QString &longOption) :
    m_option(option),
    m_optionType(optionArgument),
    m_dataType(dataType),
    m_longOption(longOption),
    m_pSwitch(NULL)
{
    if (formatString.isEmpty()) {
        switch (dataType) {
        case QVariant::Date:
            m_formatString = QString("d-M-yyyy");
            break;
        case QVariant::DateTime:
            m_formatString = QString("d-M-yyyy+h:m");
            break;
        case QVariant::Time:
            m_formatString = QString("h:m");
            break;
        default:
            m_formatString = QString();
            break;
        }
    }
}

/**
 * Creates a initialized switch option object.
 * @param parent        The OptionDefinition object which owns this Private object.
 * @param option
 * @param pSwitch
 * @param longOption
 */
OptionDefinition::Private::Private(const char option, bool *pSwitch, const QString &longOption) :
    m_option(option),
    m_optionType(SwitchOn),
    m_dataType(QVariant::Invalid),
    m_longOption(longOption),
    m_pSwitch(pSwitch)
{

}

/**
 * Copy constructor of private part.
 * @param rhs       The object to copy.
 */
OptionDefinition::Private::Private(OptionDefinition::Private* rhs) :
    m_option(rhs->m_option),
    m_optionType(rhs->m_optionType),
    m_dataType(rhs->m_dataType),
    m_formatString(rhs->m_formatString),
    m_longOption(rhs->m_longOption),
    m_pSwitch(rhs->m_pSwitch)
{

}

// ---------------------------------------------------------------------------------------------------------
// class OptionDefinition

/**
 * Standard constructor
 */
OptionDefinition::OptionDefinition() :
    d(new Private())
{

}

/**
 * Constructs a initialized OptionDefinition object.
 * @param option            The option character.
 * @param longOption        Optional. If option additional should be a word.
 * @param optionArgument    NeedArgument, NoArgument, SwitchOn and OptionalArgument.
 * @param dataType          A QVariant data type in witch a value is converted.
 * @param formatString      A string to describe how a value should be parsed. QDate, QDateTime and QTime.
 * @param longOption        A long name for a option.
 */
OptionDefinition::OptionDefinition(const char option, const OptionType optionArgument,
                                   const QVariant::Type dataType, const QString &formatString, const QString &longOption) :
    d(new Private(option, optionArgument, dataType, formatString, longOption))
{

}

/**
 * Constructs a initialized OptionDefinition object.
 * This definition takes a pointer to a boolean to switch it on (to true)
 * if this option is chosen from the user.
 * @param option
 * @param pSwitch
 * @param longOption
 */
OptionDefinition::OptionDefinition(const char option, bool *pSwitch, const QString &longOption) :
    d(new Private(option, pSwitch, longOption))
{

}

/**
 * Copy constructor for OptionDefinition objects.
 * @param rhs       The object to copy.
 */
OptionDefinition::OptionDefinition(const OptionDefinition& rhs) :
    d(new Private(rhs.d))
{

}

/**
 * Virtual
 * Destructor
 * Removes Private object from heap.
 */
OptionDefinition::~OptionDefinition()
{
    delete d;
}

/**
 * Getter
 * @return      The option char symbol.
 */
char OptionDefinition::option() const
{
    return d->m_option;
}

/**
 * Getter
 * @return      The data type of options argument.
 */
QVariant::Type OptionDefinition::dataType() const
{
    return d->m_dataType;
}

/**
 * Getter
 * @return      The long name string of the option.
 */
QString OptionDefinition::longOptionName() const
{
    return d->m_longOption;
}

/**
 * Getter
 * @return      The format string of a time or date value which is used for paesing.
 */
QString OptionDefinition::formatString() const
{
    return d->m_formatString;
}

/**
 * Setter
 * @param option    The option char for this definition.
 */
void OptionDefinition::setOption(const char option)
{
    d->m_option = option;
}

/**
 * Setter
 * @param type      The QVariant data type for the options argument.
 */
void OptionDefinition::setDataType(const QVariant::Type type)
{
    d->m_dataType = type;
}

/**
 * Setter
 * @param longName      The optional long name for an option.
 */
void OptionDefinition::setLongOptionName(const QString &longName)
{
    d->m_longOption = longName;
}

/**
 * Setter
 * @param format    A format string to parse date and time values.
 */
void OptionDefinition::setFormatString(const QString &format)
{
    d->m_formatString = format;
}

/**
 * Setter
 * @param pSwitch   A bool pointer to the value whch is to switch.
 */
void OptionDefinition::setSwitchLink(const bool * const pSwitch)
{
    d->m_pSwitch = const_cast<bool*>(pSwitch);
}

/**
 * Setter
 * @param state     Set the linked boolean value to state.
 */
void OptionDefinition::setSwitch(const bool state)
{
    *d->m_pSwitch = state;
}

/**
 * Getter
 * @return      The type of option argument if it is required, optional or no argument is taken.
 */
bool OptionDefinition::requireValue() const
{
    return d->m_optionType == RequireArgument;
}

/**
 * Getter
 * @return      True if option takes an argument.
 */
bool OptionDefinition::takesValue() const
{
    return d->m_optionType == OptionalArgument || d->m_optionType == RequireArgument;
}

/**
 * Getter
 * @return      True if the OptionDefinition object is valid.
 */
bool OptionDefinition::isValid() const
{
    return d->m_optionType != InvalidDefinition;
}

/**
 * Getter
 * @return      True if this option switches a boolean to true.
 */
bool OptionDefinition::isSwitch() const
{
    return d->m_optionType == SwitchOn;
}

/**
 * @brief OptionDefinition::convertValue
 * @param stringValue
 * @return
 */
QVariant OptionDefinition::convertValue(const QString &stringValue) const
{
    QVariant value(QVariant::Invalid);
    switch (d->m_dataType) {
    case QVariant::Bool:
        value.setValue(convertToBool(stringValue));
        break;
    case QVariant::Date:
        value.setValue(convertToDate(stringValue));
        break;
    case QVariant::DateTime:
        value.setValue(convertToDateTime(stringValue));
        break;
    case QVariant::Double:
        value.setValue(convertToDouble(stringValue));
        break;
    case QVariant::Int:
        value.setValue(convertToInt(stringValue));
        break;
    case QVariant::LongLong:
        value.setValue(convertToLongLong(stringValue));
        break;
    case QVariant::String:
        value.setValue(stringValue);
        break;
    case QVariant::Time:
        value.setValue(convertToTime(stringValue));
        break;
    case QVariant::UInt:
        value.setValue(convertToUInt(stringValue));
        break;
    case QVariant::ULongLong:
        value.setValue(convertToULongLong(stringValue));
        break;
    default:
        break;
    }

    return value;
}

/**
 * Asignment operator overload.
 * Must delete old Private object and allocate a new Private object.
 * The new Private object must be a copy of the object which is
 * asigned to this one.
 * @param rhs
 * @return
 */
OptionDefinition& OptionDefinition::operator = (const OptionDefinition& rhs)
{
    delete d;
    d = new Private(rhs.d);

    return *this;
}

/**
 * Virtual
 * Converts a string value to a boolean value.
 * Recognized strings are '1', 't', 'T', 'ture' and 'True'. These strings will
 * lead to a return value of true. All other content in the string
 * will lead to a return value of false.
 * @param stringValue
 * @return
 */
bool OptionDefinition::convertToBool(const QString &stringValue) const
{
    QString string = stringValue.toLower();
    if (string == QString("1")) {
        return true;
    }
    if (string == QString("t")) {
        return true;
    }
    if (string == QString("true")) {
        return true;
    }

    return false;
}

/**
 * Convert a string value to a QDate value.
 * A string like 3-5-2016 will lead to a date of '3.March 2016'.
 * Warning: A string like 3-5-16 will lead to a date of '3.March 1916'.
 * @param stringValue
 * @return A valid date if possible. Otherwise a invalid date.
 */
QDate OptionDefinition::convertToDate(const QString &stringValue) const
{
    return QDate::fromString(stringValue, d->m_formatString);
}

/**
 * Converts a string value to a QDateTime value.
 * The string must have a specific format. It must start with the number of day in
 * month. Next if the number of month and than the number of year with four digits.
 * All seperated with a '-'. The date and time value must be seperated with a '+'.
 * Than follows the houre and minute seperated with a colon.
 * E.g. 13-7-2016+14:30     13.July 2016 at 2:30 p.m.
 * @param stringValue
 * @return                  A valid QDateTime object if possible.
 */
QDateTime OptionDefinition::convertToDateTime(const QString &stringValue) const
{
    return QDateTime::fromString(stringValue, d->m_formatString);
}

/**
 * Converts a string value to a double value.
 * The toDouble() function of QString is used for this task.
 * @param stringValue
 * @return
 */
double OptionDefinition::convertToDouble(const QString &stringValue) const
{
    return stringValue.toDouble();
}

/**
 * Converts a string value to an int value.
 * The toInt() function of QString is used for this task.
 * @param stringValue
 * @return
 */
int OptionDefinition::convertToInt(const QString &stringValue) const
{
    return stringValue.toInt();
}

/**
 * Converts a string value to a qlonglong value.
 * The toLongLong() function of QString is used for this task.
 * @param stringValue
 * @return
 */
qlonglong OptionDefinition::convertToLongLong(const QString &stringValue) const
{
    return stringValue.toLongLong();
}

/**
 * Converts a string value to a QTime object.
 * Uses the static fromString() function of class QTime.
 * @param stringValue
 * @return
 */
QTime OptionDefinition::convertToTime(const QString &stringValue) const
{
    return QTime::fromString(stringValue, d->m_formatString);
}

/**
 * Converts a string value to a uint value.
 * The toUInt() function of QString is used for this task.
 * @param stringValue
 * @return
 */
uint OptionDefinition::convertToUInt(const QString &stringValue) const
{
    return stringValue.toUInt();
}

/**
 * Converts a string value to a qulonglong value.
 * The toULongLong() function of QString is used for this task.
 * @param stringValue
 * @return
 */
qulonglong OptionDefinition::convertToULongLong(const QString &stringValue) const
{
    return stringValue.toULongLong();
}

