#ifndef KQPOSTGRESQLRESULT_H
#define KQPOSTGRESQLRESULT_H

#include "kqpostgresqldriver.h"
#include <QSqlResult>


class KQPostgreSqlResult : public QSqlResult
{
    friend class KQPostgreSqlDriver;
public:
    ~KQPostgreSqlResult();

    QVariant handle() const override;

protected:
    explicit KQPostgreSqlResult(const QSqlDriver* driver);
    // QSqlResult interface
    QVariant data(int i) override;
    bool isNull(int i) override;
    bool reset(const QString &sqlquery) override;
    bool fetch(int i) override;
    bool fetchFirst() override;
    bool fetchLast() override;
    int numRowsAffected() override;
    QSqlRecord record() const override;
    bool prepare(const QString &query) override;
    bool exec() override;
    int size() override;

private:
    // Concret class members
    void clearResult();
    QString replaceStandardPlaceholders(QString sqlStatement, bool &ok) const;
    QString replaceNamedPlacholders(QString sqlStatement, bool& ok);
    QString replacePlaceholder(QString &sqlStatement, const int startPos, const QString &placeholder);
    char** cstringArrayOfSize(const int size) const;
    void freeCStringArray(char** array, const int size);
    char* stringCopy(const QString& origin) const;
    QString variantToString(const QVariant& value) const;
    bool isPrepared(const QString& stmtName) const;
    void executePreparedStmt();
    QVariant::Type variantTypeFromPostgreType(const Oid type) const;

private:
    PGresult* m_pResult;
    int m_currentSize;
};

#endif // KQPOSTGRESQLRESULT_H
