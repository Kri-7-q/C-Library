#ifndef KQPOSTGRESQLDRIVER_H
#define KQPOSTGRESQLDRIVER_H

#include <libpq-fe.h>
#include <QSqlDriver>
#include <QSqlError>
#include <QString>
#include <QSqlRecord>

class KQPostgreSqlResult;

class KQPostgreSqlDriver : public QSqlDriver
{

public:
    KQPostgreSqlDriver();
    ~KQPostgreSqlDriver();

signals:

public slots:

    // QSqlDriver interface
public:
    QVariant handle() const override;
    bool hasFeature(DriverFeature f) const override;
    void close() override;
    QSqlResult *createResult() const override;
    bool open(const QString &db,
              const QString &user = QString(),
              const QString &password = QString(),
              const QString &host = QString(),
              int port = -1,
              const QString &connOpts = QString()) override;
    bool isOpen() const override;
    QSqlRecord record(const QString &tableName) const override;

protected:
    bool splitSchemaName(QString& tablename, QString& schemaName) const;

private:
    PGconn* m_pConnection;
};

#endif // KQPOSTGRESQLDRIVER_H
