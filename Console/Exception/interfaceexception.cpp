#include "interfaceexception.h"

/**
 * @brief InterfaceException::InterfaceException
 */
InterfaceException::InterfaceException()
{

}

/**
 * @brief InterfaceException::InterfaceException
 * @param className
 * @param functionName
 * @param errorMsg
 */
InterfaceException::InterfaceException(const QString &className, const QString &functionName, const QString &errorMsg) :
    m_className(className),
    m_functionName(functionName),
    m_errorMsg(errorMsg)
{

}

/**
 * @brief InterfaceException::InterfaceException
 * @param origin
 */
InterfaceException::InterfaceException(const InterfaceException &origin) :
    m_className(origin.m_className),
    m_functionName(origin.m_functionName),
    m_errorMsg(origin.m_errorMsg)
{

}

// Getter
QString InterfaceException::className() const
{
    return m_className;
}

// Setter
void InterfaceException::setClassName(const QString &className)
{
    m_className = className;
}

// Getter
QString InterfaceException::functionName() const
{
    return m_functionName;
}

// Setter
void InterfaceException::setFunctionName(const QString &functionName)
{
    m_functionName = functionName;
}

// Getter
QString InterfaceException::errorMsg() const
{
    return m_errorMsg;
}

// Setter
void InterfaceException::setErrorMsg(const QString &errorMsg)
{
    m_errorMsg = errorMsg;
}

// Override helper function.
void InterfaceException::raise() const
{
    throw *this;
}

// Override helper function
InterfaceException *InterfaceException::clone() const
{
    return new InterfaceException(*this);
}
