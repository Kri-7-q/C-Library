#include "kqpostgresqldriver.h"
#include "kqpostgresqlresult.h"
#include <QSqlQuery>
#include <QSqlField>
#include <QDebug>

Q_DECLARE_OPAQUE_POINTER(PGconn*)
Q_DECLARE_METATYPE(PGconn*)


/**
 * Standard Constructor for the driver.
 */
KQPostgreSqlDriver::KQPostgreSqlDriver() :
    m_pConnection(NULL)
{
    setOpen(false);
}

/**
 * Destructor of PostgreSql driver.
 */
KQPostgreSqlDriver::~KQPostgreSqlDriver()
{
    if (m_pConnection) {
        PQfinish(m_pConnection);
        m_pConnection = NULL;
    }
}

/**
 * A hadle to the PostgreSql connection object.
 * Returns the PGconn structure pointer wrapped in
 * an QVariant object.
 * @return      PGconn pointer in a QVariant object.
 */
QVariant KQPostgreSqlDriver::handle() const
{
    return QVariant::fromValue(m_pConnection);
}

/**
 * Qveride
 * Returns true if this driver supports the requested feature. Otherwise return false.
 * @param f         A driver feature.
 * @return          True if driver has this feature.
 */
bool KQPostgreSqlDriver::hasFeature(QSqlDriver::DriverFeature f) const
{
    switch (f) {
    case QSqlDriver::Transactions:
        return false;
        break;
    case QSqlDriver::QuerySize:
        return true;
        break;
    case QSqlDriver::BLOB:
        return false;
        break;
    case QSqlDriver::Unicode:
        return false;
        break;
    case QSqlDriver::PreparedQueries:
        return true;
        break;
    case QSqlDriver::NamedPlaceholders:
        return true;
        break;
    case QSqlDriver::LastInsertId:
        return false;
        break;
    case QSqlDriver::BatchOperations:
        return false;
        break;
    case QSqlDriver::SimpleLocking:
        return false;
        break;
    case QSqlDriver::LowPrecisionNumbers:
        return false;
        break;
    case QSqlDriver::EventNotifications:
        return false;
        break;
    case QSqlDriver::FinishQuery:
        return true;
        break;
    case QSqlDriver::MultipleResultSets:
        return false;
        break;
    case QSqlDriver::CancelQuery:
        return false;
        break;
    default:
        break;
    }

    return false;
}

/**
 * Override
 * Close an open database connection.
 */
void KQPostgreSqlDriver::close()
{
    if (m_pConnection && isOpen()) {
        PQfinish(m_pConnection);
        m_pConnection = NULL;
        setOpenError(false);
        setOpen(false);
    }
}

/**
 * Override
 * Creates a QSqlResult object. (Factory)
 * @return          A pointer to the object.
 */
QSqlResult *KQPostgreSqlDriver::createResult() const
{
    return new KQPostgreSqlResult(this);
}

/**
 * Override
 * Open a connection to the database.
 * @param db            The name of the database which is to open.
 * @param user          A username of a database role.
 * @param password      The password to the username.
 * @param host          The host name or address where the database is home.
 * @param port          The port number to the database.
 * @param connOpts      Additional and optional options.
 * @return              True if database is open. Otherwise returns false.
 */
bool KQPostgreSqlDriver::open(const QString &db, const QString &user, const QString &password,
                              const QString &host, int port, const QString &connOpts)
{
    qDebug() << "Driver: Open database ...";
    if (isOpen()) {
        close();
    }
    qDebug() << "Driver: Create connection string ...";
    QString prototype("host=%1 port=%2 dbname=%3 user=%4 password=%5");
    QString connectionInfo = prototype.arg(host).arg(port).arg(db).arg(user).arg(password);
    if (! connOpts.isEmpty()) {
        QString options = QString(connOpts).replace(QChar(';'), QChar(' '));
        connectionInfo.append(' ').append(options);
    }
    qDebug() << "Connection string: " << connectionInfo;
    QByteArray info = connectionInfo.toLocal8Bit();
    m_pConnection = PQconnectdb(info.data());
    ConnStatusType status = PQstatus(m_pConnection);
    if (status == CONNECTION_BAD) {
        QSqlError error(QString("Could not open database !"), QString(PQerrorMessage(m_pConnection)),
                        QSqlError::ConnectionError);
        setLastError(error);
        setOpenError(true);
        PQfinish(m_pConnection);
        m_pConnection = NULL;

        return false;
    }
    setOpenError(false);

    return true;
}

/**
 * Tests if a database connection is open.
 * @return      True if connection is open.
 */
bool KQPostgreSqlDriver::isOpen() const
{
    if (m_pConnection == NULL) {
        return false;
    }
    ConnStatusType status = PQstatus(m_pConnection);
    
    return status == CONNECTION_OK;
}

/**
 * Get table information.
 * @param tableName
 * @return
 */
QSqlRecord KQPostgreSqlDriver::record(const QString &tableName) const
{
    QSqlRecord info;
    if (! isOpen()) {
        return info;
    }
    QString table(tableName.toLower()), schema;
    splitSchemaName(table, schema);
    QString stmt("select pg_attribute.attname, pg_attribute.atttypid::int, "
            "pg_attribute.attnotnull, pg_attribute.attlen, pg_attribute.atttypmod, "
            "pg_attrdef.adsrc "
            "from pg_class, pg_attribute "
            "left join pg_attrdef on (pg_attrdef.adrelid = "
            "pg_attribute.attrelid and pg_attrdef.adnum = pg_attribute.attnum) "
            "where %1 "
            "and pg_class.relname = '%2' "
            "and pg_attribute.attnum > 0 "
            "and pg_attribute.attrelid = pg_class.oid "
            "and pg_attribute.attisdropped = false "
            "order by pg_attribute.attnum ");
    if (schema.isEmpty()) {
        stmt = stmt.arg(QString("pg_table_is_visible(pg_class.oid)"));
    } else {
        stmt = stmt.arg(QString::fromLatin1("pg_class.relnamespace = (select oid from "
               "pg_namespace where pg_namespace.nspname = '%1')").arg(schema));
    }
    stmt = stmt.arg(table);
    QSqlQuery query(createResult());
    if (! query.exec(stmt)) {
        // If can not execute statement then return an empty record.
        return info;
    }
    KQPostgreSqlResult* result = (KQPostgreSqlResult*)query.result();
    while (query.next()) {
        int len = query.value(3).toInt();
        int precision = query.value(4).toInt();
        // swap length and precision if length == -1
        if (len == -1 && precision > -1) {
            len = precision - 4;
            precision = -1;
        }
        QString defVal = query.value(5).toString();
        if (!defVal.isEmpty() && defVal.at(0) == QLatin1Char('\''))
            defVal = defVal.mid(1, defVal.length() - 2);
        QSqlField f(query.value(0).toString(), result->variantTypeFromPostgreType(query.value(1).toInt()));
        f.setRequired(query.value(2).toBool());
        f.setLength(len);
        f.setPrecision(precision);
        f.setDefaultValue(defVal);
        f.setSqlType(query.value(1).toInt());
        info.append(f);
    }

    return info;
}

/**
 * Seperate tablename from schema name.
 * These names are seperated via a dot in the string.
 * @param tablename         A reference containing schema notation. Will be modified to pure tablename.
 * @param schemaName        A reference to an empty string. Will be overwritten if it is not empty.
 * @return                  True if names are seperated.
 */
bool KQPostgreSqlDriver::splitSchemaName(QString &tablename, QString &schemaName) const
{
    int dot = tablename.indexOf(QChar('.'));
    if (dot < 0) {
        return false;
    }
    schemaName = tablename.left(dot);
    tablename = tablename.mid(dot);

    return true;
}
