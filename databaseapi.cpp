#include "DatabaseAPI.h"

DatabaseAPI::DatabaseAPI(QObject *parent) : QObject(parent) {}

DatabaseAPI::~DatabaseAPI() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseAPI::connectToDatabase(const QString &host, const QString &dbName, const QString &user, const QString &password) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseAPI::addUser(const QString &username, const QString &password, const QString &email, const QString &role) {
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password, email, role) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(role);

    if (!query.exec()) {
        qDebug() << "Add User Error: " << query.lastError().text();
        return false;
    }
    return true;
}

QVector<QVariantMap> DatabaseAPI::getAllMembers() {
    QVector<QVariantMap> members;
    QSqlQuery query("SELECT * FROM Members");

    while (query.next()) {
        QVariantMap member;
        member["member_id"] = query.value("member_id").toInt();
        member["first_name"] = query.value("first_name").toString();
        member["last_name"] = query.value("last_name").toString();
        member["date_of_birth"] = query.value("date_of_birth").toDate();
        member["phone_number"] = query.value("phone_number").toString();
        member["membership_start_date"] = query.value("membership_start_date").toDate();
        member["membership_end_date"] = query.value("membership_end_date").toDate();
        members.append(member);
    }
    return members;
}

bool DatabaseAPI::addMember(int userId, const QString &firstName, const QString &lastName, const QDate &dob, const QString &phoneNumber,
                            const QDate &membershipStart, const QDate &membershipEnd) {
    QSqlQuery query;
    query.prepare("INSERT INTO Members (user_id, first_name, last_name, date_of_birth, phone_number, membership_start_date, membership_end_date) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(dob);
    query.addBindValue(phoneNumber);
    query.addBindValue(membershipStart);
    query.addBindValue(membershipEnd);

    if (!query.exec()) {
        qDebug() << "Add Member Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseAPI::addAttendance(int memberId, const QDate &date, const QString &status) {
    QSqlQuery query;
    query.prepare("INSERT INTO Attendance (member_id, date, status) VALUES (?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(date);
    query.addBindValue(status);

    if (!query.exec()) {
        qDebug() << "Add Attendance Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseAPI::addPayment(int memberId, double amount, const QDate &paymentDate, const QString &method) {
    QSqlQuery query;
    query.prepare("INSERT INTO Payments (member_id, amount, payment_date, payment_method) VALUES (?, ?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(amount);
    query.addBindValue(paymentDate);
    query.addBindValue(method);

    if (!query.exec()) {
        qDebug() << "Add Payment Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseAPI::addClass(const QString &className, const QString &instructor, const QDateTime &scheduleTime) {
    QSqlQuery query;
    query.prepare("INSERT INTO Classes (class_name, instructor, schedule_time) VALUES (?, ?, ?)");
    query.addBindValue(className);
    query.addBindValue(instructor);
    query.addBindValue(scheduleTime);

    if (!query.exec()) {
        qDebug() << "Add Class Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseAPI::registerClass(int memberId, int classId, const QDate &registrationDate) {
    QSqlQuery query;
    query.prepare("INSERT INTO Class_Registrations (member_id, class_id, registration_date) VALUES (?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(classId);
    query.addBindValue(registrationDate);

    if (!query.exec()) {
        qDebug() << "Register Class Error: " << query.lastError().text();
        return false;
    }
    return true;
}
