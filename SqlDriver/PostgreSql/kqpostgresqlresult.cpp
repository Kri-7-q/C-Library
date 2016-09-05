#include "kqpostgresqlresult.h"
#include <QDateTime>
#include <QSqlField>
#include <QSqlRecord>
#include <QString>
#include <QDebug>

Q_DECLARE_OPAQUE_POINTER(PGresult*)
Q_DECLARE_METATYPE(PGresult*)
Q_DECLARE_OPAQUE_POINTER(PGconn*)
Q_DECLARE_METATYPE(PGconn*)


/**
 * Constructor
 * Takes a pointer to a KQPostgreSqlDriver object.
 * @param driver    Pointer to the database driver.
 */
KQPostgreSqlResult::KQPostgreSqlResult(const QSqlDriver *driver) :
    QSqlResult(driver),
    m_pResult(NULL),
    m_currentSize(-1)
{
    
}

/**
 * Destructor
 * Free used memory.
 */
KQPostgreSqlResult::~KQPostgreSqlResult()
{
    if (m_pResult) {
        PQclear(m_pResult);
    }
}

/**
 * A handle wrapped in a QVariant to the PGresult object.
 * @return
 */
QVariant KQPostgreSqlResult::handle() const
{
    return QVariant::fromValue(m_pResult);
}

/**
 * Override
 * Get data of a field as QVariant.
 * @param i     Field number.
 * @return      The value as QVariant or QVariant().
 */
QVariant KQPostgreSqlResult::data(int i)
{
    if (m_pResult == NULL || i > PQnfields(m_pResult)) {
        qWarning("Field number is out of range. Or has no result.");
        return QVariant();
    }
    Oid typeOid = PQftype(m_pResult, i);
    QVariant::Type dataType = variantTypeFromPostgreType(typeOid);
    if (PQgetisnull(m_pResult, at(), i)) {
        return QVariant(dataType);
    }
    const char* value = PQgetvalue(m_pResult, at(), i);
    switch (dataType) {
    case QVariant::Bool:
        return QVariant((bool)(value[0] == 't'));
        break;
    case QVariant::String:
        return QVariant(QString(value));
        break;
    case QVariant::LongLong:
        return QVariant(QString(value).toLongLong());
        break;
    case QVariant::Int:
        return QVariant(atoi(value));
        break;
    case QVariant::Double:
        if (typeOid == 1700) {
            if (numericalPrecisionPolicy() != QSql::HighPrecision) {
                QVariant retval;
                bool convert;
                double dbl=QString(value).toDouble(&convert);
                if (numericalPrecisionPolicy() == QSql::LowPrecisionInt64)
                    retval = (qlonglong)dbl;
                else if (numericalPrecisionPolicy() == QSql::LowPrecisionInt32)
                    retval = (int)dbl;
                else if (numericalPrecisionPolicy() == QSql::LowPrecisionDouble)
                    retval = dbl;
                if (!convert)
                    return QVariant();
                return retval;
            }
            return QVariant(QString(value));
        }
        return QVariant(QString(value).toDouble());
        break;
    case QVariant::Date:
        return QVariant(QDate::fromString(QString(value), Qt::ISODate));
        break;
    case QVariant::Time:
        return QVariant(QTime::fromString(QString(value), Qt::ISODate));
        break;
    case QVariant::DateTime:
        return QVariant(QDateTime::fromString(QString(value), Qt::ISODate));
        break;
    case QVariant::ByteArray: {
        size_t length = 0;
        unsigned char* buffer = PQunescapeBytea((unsigned char*)value, &length);
        QByteArray array((char*)buffer, length);
        PQfreemem(buffer);
        return QVariant(array);
        break;
    }
    default:
        qWarning("Unknown data type !");
        break;
    }

    return QVariant();
}

/**
 * Override
 * Lookup if a value in result is NULL.
 * @param i     The field index of result value.
 * @return      True if value is NULL.
 */
bool KQPostgreSqlResult::isNull(int i)
{
    return PQgetisnull(m_pResult, at(), i);
}

/**
 * Override
 * Reset result to a given prepared statement.
 * @param sqlquery      The name of prepared statement.
 * @return              True if result is present.
 */
bool KQPostgreSqlResult::reset(const QString &sqlquery)
{
    clearResult();
    if (!driver()) {
        return false;
    }
    if (!driver()->isOpen() || driver()->isOpenError()) {
        return false;
    }
    setQuery(sqlquery);

    return exec();
}

/**
 * Override
 * Sets the result to the given row.
 * @param i     The number of where result should be set to.
 * @return      True if done.
 */
bool KQPostgreSqlResult::fetch(int i)
{
    if (! isActive()) {
        return false;
    }
    if (i < 0 || i >= PQntuples(m_pResult)) {
        return false;
    }
    if (i == at()) {
        return false;
    }
    setAt(i);

    return true;
}

/**
 * Override
 * Sets the result to the first row.
 * @return  True if done.
 */
bool KQPostgreSqlResult::fetchFirst()
{
    return fetch(0);
}

/**
 * Override
 * Sets the result to the last row.
 * @return  True if done.
 */
bool KQPostgreSqlResult::fetchLast()
{
    return fetch(PQntuples(m_pResult) - 1);
}

/**
 * Override
 * Get the number of rows which was affected by the las statement.
 * @return          The number of affected rows.
 */
int KQPostgreSqlResult::numRowsAffected()
{
    char* strValue = PQcmdTuples(m_pResult);
    char** errorPos = NULL;
    long value = strtol(strValue, errorPos, 10);
    if (**errorPos != '\0') {
        PGconn* pConnection = driver()->handle().value<PGconn*>();
        QSqlError error(QString("Could not get information about affected rows !"), PQerrorMessage(pConnection),
                        QSqlError::UnknownError, PQresultStatus(m_pResult));
        setLastError(error);
    }

    return (int)value;
}

/**
 * Override
 * Get a info record about the result. A QSqlRecord object
 * containing information about the query result.
 * For instance: column name, data type
 * @return      A record with result information.
 */
QSqlRecord KQPostgreSqlResult::record() const
{
    QSqlRecord info;
    if (!isActive() || !isSelect()) {
        return info;
    }
    int columns = PQnfields(m_pResult);
    for (int index=0; index<columns; ++index) {
        char* value = PQfname(m_pResult, index);
        QString name(value);
        int length = PQfsize(m_pResult, index);
        int precision = PQfmod(m_pResult, index);
        Oid postgreType = PQftype(m_pResult, index);
        QVariant::Type dataType = variantTypeFromPostgreType(postgreType);
        QSqlField field(name, dataType);
        field.setLength(length);
        field.setPrecision(precision);

        info.append(field);
    }

    return info;
}

/**
 * Override
 * Prepare a query for execution.
 * Let the DBMS parse the query with place holders and
 * execute them later with exec().
 * Build a string from the hash code of a SQL statement.
 * These hash code is used as statement name. With this
 * name the prepared statement can be executed.
 * The statement name is set as query. The exec() method
 * must check if the query string is a prepared or a
 * normal SQL statement.
 * @param query     The SQL query string to prepare.
 * @return          True if successfully prepared.
 */
bool KQPostgreSqlResult::prepare(const QString &query)
{
    resetBindCount();
    qDebug() << "Prepare: " << query;
    bool ok = false;
    QString stmt = replaceStandardPlaceholders(query, ok);
    if (! ok) {
        stmt = replaceNamedPlacholders(query, ok);
    }
    qDebug() << "Placeholder replaced: " << stmt;
    uint hash = qHash(query);
    QString stmtName = QString::number(hash);
    setQuery(stmtName);
    if (isPrepared(stmtName)) {
        return true;
    }
    PGconn* pConnection = driver()->handle().value<PGconn*>();
    PGresult* result = PQprepare(pConnection, stmtName.toLocal8Bit().data(), stmt.toLocal8Bit().data(), boundValueCount(), NULL);
    ExecStatusType statusType = PQresultStatus(result);
    PQclear(result);
    if (statusType != PGRES_COMMAND_OK) {
        QString databaseErr(PQerrorMessage(pConnection));
        QString code(PQresStatus(statusType));
        QSqlError error(QString("Could not prepare SQL statement !"), databaseErr, QSqlError::StatementError,code);
        setLastError(error);
        return false;
    }

    return true;
}

/**
 * Execute a previously prepared statement.
 * @return      True if done.
 */
bool KQPostgreSqlResult::exec()
{
    qDebug() << "exec(): " << lastQuery();
    if (lastQuery().at(0).isDigit()) {
        // Is a prepared statment.
        executePreparedStmt();
    } else {
        // Is a SQL query.
        PGconn* pConnection = driver()->handle().value<PGconn*>();
        m_pResult = PQexec(pConnection, lastQuery().toLocal8Bit().data());
    }
    ExecStatusType status = PQresultStatus(m_pResult);
    if (status == PGRES_TUPLES_OK) {
        setActive(true);
        setSelect(true);
        m_currentSize = PQntuples(m_pResult);
        return true;
    }
    if (status == PGRES_COMMAND_OK) {
        setActive(true);
        setSelect(false);
        m_currentSize = -1;
        return true;
    }
    QSqlError error(QString("Could not execute query !"), QString(PQresultErrorMessage(m_pResult)), QSqlError::StatementError,
                    QString(PQresStatus(status)));
    setLastError(error);
    clearResult();

    return false;
}

/**
 * Get the size of result.
 * @return      The number of rows in result.
 */
int KQPostgreSqlResult::size()
{
    return m_currentSize;
}

/**
 * Private
 * Get a QVariant type from a PostgreSql data type.
 * @param type      A PostgreSql Oid with data type information.
 * @return          A QVariant::Type similar to the Postgre type.
 */
QVariant::Type KQPostgreSqlResult::variantTypeFromPostgreType(const Oid type) const
{
    QVariant::Type variantType = QVariant::Invalid;
    switch (type) {
    case 16:        // bool
        variantType = QVariant::Bool;
        break;
    case 20:        // int8
        variantType = QVariant::LongLong;
        break;
    case 21:        // int2
    case 23:        // int4
    case 2278:      // oid
    case 24:        // regproc
    case 28:        // xid
    case 29:        // cid
        variantType = QVariant::Int;
        break;
    case 1700:      // numeric
    case 700:       // float4
    case 701:       // float8
        variantType = QVariant::Double;
        break;
    case 702:       // abstime
    case 703:       // reltime
    case 1082:      // date
        variantType = QVariant::Date;
        break;
    case 1083:      // time
    case 1266:      // timetz
        variantType = QVariant::Time;
        break;
    case 1114:      // timestamp
    case 1184:      // timestamptz
        variantType = QVariant::DateTime;
        break;
    case 17:        // bytea
        variantType = QVariant::ByteArray;
        break;
    default:
        variantType = QVariant::String;
        break;
    }
    
    return variantType;
}

/**
 * Protected
 * Delete result from memory.
 */
void KQPostgreSqlResult::clearResult()
{
    if (m_pResult) {
        PQclear(m_pResult);
        m_pResult = NULL;
        setAt(QSql::BeforeFirstRow);
        setActive(false);
        m_currentSize = -1;
    }
}

/**
 * Serches for SQL placeholders like '?'.
 * Found placeholders are replaced with: '$1','$2','$3'...
 * The Dollar symbol and the number of placeholer is as
 * it is managed by the PosgreSql server.
 * @param sqlStatement      A statement with placeholders.
 * @return sqlStatement     With PostgreSql placeholders.
 */
QString KQPostgreSqlResult::replaceStandardPlaceholders(QString sqlStatement, bool& ok) const
{
    // Replace standard placeholders '?' if they are used.
    int position = sqlStatement.indexOf(QChar('?'), 0);
    ok = false;
    if (position < 0) {
        return sqlStatement;
    }
    int numPlaceholder = 1;
    QChar currentPlaceholder[2] = { QChar('$'), QChar('0') };
    while (position > 0) {
        currentPlaceholder[1] = QChar('0' + numPlaceholder);
        sqlStatement.replace(position, 1, currentPlaceholder, 2);
        ++numPlaceholder;
        position = sqlStatement.indexOf(QChar('?'), position);
    }
    ok = true;

    return sqlStatement;
}

/**
 * Replaces named placeholders in SQL statements. Placeholders are
 * replaced with PosgreSql placeholders. They are named $1, $2, $3, ...
 * @param sqlStatement      A SQL statement string.
 * @param ok                Reference to a bool value. Is set to true if done.
 * @return sqlStatement     The modified SQL statement.
 */
QString KQPostgreSqlResult::replaceNamedPlacholders(QString sqlStatement, bool &ok)
{
    int position = sqlStatement.indexOf(QChar(':'), 0);
    ok = false;
    if (position < 0) {
        return sqlStatement;
    }
    int numPlaceHolder = 1;
    while (position > 0) {
        QString placeholder = QString('$').append(QString::number(numPlaceHolder));
        QString placeholderName = replacePlaceholder(sqlStatement, position, placeholder);
        bindValue(placeholderName, QVariant(), QSql::In);
        position += placeholder.length();
        position = sqlStatement.indexOf(QChar(':'), position);
        ++numPlaceHolder;
    }

    return sqlStatement;
}

/**
 * Parse the name of the placeholder in SQL query and replaces it with
 * PosgreSql placeholder. ($1, $2, $3, ...)
 * Start parsing from the given position. Gives back the end position
 * of the placeholder. Placeholder starts with a colon and it ends
 * with a none letter character.
 * @param sqlStatement      The SQL statement with named placeholders.
 * @param startPos          Position of a found colon which indicates a placeholder.
 * @param placeholder       Placeholder string like '$1'.
 * @return                  A string with the name of placeholder.
 */
QString KQPostgreSqlResult::replacePlaceholder(QString& sqlStatement, const int startPos, const QString& placeholder)
{
    int endPos = startPos + 1;
    while (sqlStatement.at(endPos).isLetter() && endPos < sqlStatement.length()) {
        ++endPos;
    }
    QString placeholderName = sqlStatement.mid(startPos, endPos - startPos);
    sqlStatement.replace(startPos, endPos-startPos, placeholder);

    return placeholderName;
}

/**
 * Creates an array of char pointer with given size.
 * Array content is set to NULL.
 * @param size
 * @return
 */
char **KQPostgreSqlResult::cstringArrayOfSize(const int size) const
{
    char** array = new char*[size];
    for (int index=0; index<size; ++index) {
        array[index] = NULL;
    }

    return array;
}

/**
 * Private
 * Free memory of an allocated char pointer array.
 * Delete the arrays content and the array it self.
 * @param array     The array to delete.
 * @param size      The size of the array.
 */
void KQPostgreSqlResult::freeCStringArray(char **array, const int size)
{
    for (int index=0; index<size; ++index) {
        if (array[index] != NULL) {
            delete array[index];
        }
    }
    delete array;
}

/**
 * Copy QString to cstring.
 * Creates a string in heap and return a pointer to it.
 * @param origin
 * @return string       A null terminated cstring pointer.
 */
char *KQPostgreSqlResult::stringCopy(const QString &origin) const
{
    QByteArray source = origin.toLocal8Bit();
    int length = source.length();
    char* string = new char[length + 1];
    for (int index=0; index<source.size(); ++index) {
        string[index] = source.at(index);
    }
    string[length] = 0;

    return string;
}

/**
 * Converts a QVariant value to a QString which can be inserted in
 * the parameter array of a prepared statment.
 * @param value     The value which is to convert.
 * @return string   The converted value. Or empty string.
 */
QString KQPostgreSqlResult::variantToString(const QVariant &value) const
{
    QVariant::Type dataType = value.type();
    switch (dataType) {
    case QVariant::Bool:
        if (value.toBool()) {
            return QString("t");
        } else {
            return QString("f");
        }
        break;
    case QVariant::LongLong:
    case QVariant::Int:
    case QVariant::Double:
    case QVariant::String:
        return value.toString();
        break;
    case QVariant::Date:
        return value.toDate().toString(Qt::ISODate);
        break;
    case QVariant::Time:
        return value.toTime().toString(Qt::ISODate);
        break;
    case QVariant::DateTime:
        return value.toDateTime().toString(Qt::ISODate);
        break;
    case QVariant::ByteArray: {
        return QString(value.toByteArray());
        break;
    }
    default:
        qWarning("Unknown data type !");
        break;
    }

    return QString();
}

/**
 * Reads from PostgreSql view 'pg_prepared_statements' all known
 * prepared statements.
 * Prepared statements get names. These names are read from the view.
 * If the view of PostgreSql has stmtName than this statement was
 * prepared and can be executed.
 * @param stmtName      The statement name to search for.
 * @return              True if statement is allready prepared.
 */
bool KQPostgreSqlResult::isPrepared(const QString &stmtName) const
{
    bool isStmtPrepared = false;
    QVariant connectionHandle = driver()->handle();
    PGconn* pConnection = connectionHandle.value<PGconn*>();
    char* sqlSelect = "SELECT name FROM pg_prepared_statements";
    PGresult* result = PQexec(pConnection, sqlSelect);
    if (PQresultStatus(result) == PGRES_TUPLES_OK) {
        int rowCount = PQntuples(result);
        for (int row=0; row<rowCount; ++row) {
            char* value = PQgetvalue(result, row, 0);
            QString preparedStmtName(value);
            if (stmtName == preparedStmtName) {
                isStmtPrepared = true;
                break;
            }
        }
    }
    PQclear(result);

    return isStmtPrepared;
}

/**
 * Execute a SQL statement which is allready prepared.
 * @return
 */
void KQPostgreSqlResult::executePreparedStmt()
{
    clearResult();
    QVector<QVariant> paramVector = boundValues();
    qDebug() << "Values: " << paramVector;
    // Allocate memory for bind values.
    char** values = cstringArrayOfSize(paramVector.size());
    int* valueLength = new int[paramVector.size()];
    for (int index=0; index<paramVector.size(); ++index) {
        QString value = variantToString(paramVector.value(index));
        values[index] = stringCopy(value);
        valueLength[index] = value.length();
    }
    PGconn* pConnection = driver()->handle().value<PGconn*>();
    m_pResult = PQexecPrepared(pConnection, lastQuery().toLocal8Bit().data(), boundValueCount(), values, valueLength, NULL, 0);
    // Free allocated memory.
    freeCStringArray(values, paramVector.size());
    delete[] valueLength;
}
