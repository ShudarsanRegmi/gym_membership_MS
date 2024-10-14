#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QDate>

class DatabaseAPI : public QObject {
    Q_OBJECT

public:
    explicit DatabaseAPI(QObject *parent = nullptr);
    ~DatabaseAPI();

    bool connectToDatabase(const QString &host, const QString &dbName, const QString &user, const QString &password);
    bool addUser(const QString &username, const QString &password, const QString &email, const QString &role);
    QVector<QVariantMap> getAllMembers();
    bool addMember(int userId, const QString &firstName, const QString &lastName, const QDate &dob, const QString &phoneNumber,
                   const QDate &membershipStart, const QDate &membershipEnd);
    bool addAttendance(int memberId, const QDate &date, const QString &status);
    bool addPayment(int memberId, double amount, const QDate &paymentDate, const QString &method);
    bool addClass(const QString &className, const QString &instructor, const QDateTime &scheduleTime);
    bool registerClass(int memberId, int classId, const QDate &registrationDate);

private:
    QSqlDatabase db;
};

#endif // DATABASEAPI_H
