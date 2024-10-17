#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDate>
#include <QMap>
#include <QDebug>

#include "models/user.h"


struct MemberDetails {
    QString firstName;
    QString lastName;
    QDate dateOfBirth;
    QString phoneNumber;
    QDate membershipStartDate;
    QDate membershipEndDate;
};


class DatabaseAPI {
public:
    DatabaseAPI();
    ~DatabaseAPI();

    bool connectToDatabase(const QString &dbname);

    // User-related operations
    bool addUser(const QString &username, const QString &password, const QString &email, const QString &role);
    bool authenticateUser(const QString &username, const QString &password);
    QSqlQuery getUserDetails(int userId);

    // Member-related operations
    bool addMember(int userId, const QString &firstName, const QString &lastName, const QDate &dob, const QString &phoneNumber, const QDate &startDate, const QDate &endDate);
    bool updateMember(int memberId, const QMap<QString, QVariant> &updatedData);
    MemberDetails getMemberDetails(int memberId);
    QSqlQuery getAllMembers();
    bool deleteMember(int memberId);

    // Attendance-related operations
    bool markAttendance(int memberId, const QDate &date, const QString &status);
    QSqlQuery getAttendanceRecordsByMember(int memberId);
    QSqlQuery getAttendanceByDate(const QDate &date);

    // Payment-related operations
    bool addPayment(int memberId, double amount, const QDate &date, const QString &method);
    QSqlQuery getPaymentRecords(int memberId);

    // Class-related operations
    bool addClass(const QString &name, const QString &instructor, const QDateTime &scheduleTime);
    QSqlQuery getAllClasses();
    QSqlQuery getClassDetails(int classId);

    // Class registration-related operations
    bool registerForClass(int memberId, int classId);
    QSqlQuery getClassRegistrations(int classId);

    // Subscription-related operations
    bool addSubscription(int memberId, const QString &type, const QString &status);
    QSqlQuery getMemberSubscriptions(int memberId);

    // added later
    QVector<QVector<QString>> getUsers();
    QVector<QString> getUserGymDetails(const QString &userId);
    QVector<QString> getUserPersonalInfo(const QString &userId);
    QVector<User*> getAllUsers();

    QVector<QString> getCompleteUserInfo(const QString &userID); // added for admin page functionality: aaja sajh
    bool updateUserDetails(const QString &userID, const QVector<QString> &updatedDetails);
    QVector<QVector<QString>> getAttendanceReport(const QString &fromDate, const QString &toDate);

    // added at dash archalis to make attendance page functional..
    QVector<QVector<QString>> getAttendanceForDate(const QString &userId, const QDate &date);
    QVector<QVector<QString>> getAttendanceBetweenDates(const QString &userId, const QDate &fromDate, const QDate &toDate);




private:
    QSqlDatabase db;
};

#endif // DATABASEAPI_H
