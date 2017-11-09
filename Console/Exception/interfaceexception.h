#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

class InterfaceException : public QException
{
public:
    InterfaceException();
    InterfaceException(const QString& className, const QString& functionName, const QString& errorMsg);
    InterfaceException(const InterfaceException& origin);

    // Getter and setter
    QString className() const;
    void setClassName(const QString& className);
    QString functionName() const;
    void setFunctionName(const QString& functionName);
    QString errorMsg() const;
    void setErrorMsg(const QString &errorMsg);

    // Concurrent helper
    void raise() const;
    InterfaceException* clone() const;

private:
    QString m_className;
    QString m_functionName;
    QString m_errorMsg;
};

#endif // EXCEPTION_H
