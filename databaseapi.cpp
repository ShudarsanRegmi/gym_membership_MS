#include "databaseapi.h"

DatabaseAPI::DatabaseAPI() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseAPI::~DatabaseAPI() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseAPI::connectToDatabase(const QString &dbname) {
    db.setDatabaseName(dbname);

    if (!db.open()) {
        qDebug() << "Error: Could not open database." << db.lastError().text();
        return false;
    }

    return true;
}

// User-related operations
bool DatabaseAPI::addUser(const QString &username, const QString &password, const QString &email, const QString &role) {
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password, email, role) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(role);

    if (!query.exec()) {
        qDebug() << "Error adding user: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseAPI::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "Error authenticating user: " << query.lastError().text();
        return false;
    }

    return query.next();
}

QSqlQuery DatabaseAPI::getUserDetails(int userId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE user_id = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "Error fetching user details: " << query.lastError().text();
    }

    return query;
}

// Member-related operations
bool DatabaseAPI::addMember(int userId, const QString &firstName, const QString &lastName, const QDate &dob, const QString &phoneNumber, const QDate &startDate, const QDate &endDate) {
    QSqlQuery query;
    query.prepare("INSERT INTO Members (user_id, first_name, last_name, date_of_birth, phone_number, membership_start_date, membership_end_date) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(dob);
    query.addBindValue(phoneNumber);
    query.addBindValue(startDate);
    query.addBindValue(endDate);

    if (!query.exec()) {
        qDebug() << "Error adding member: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseAPI::updateMember(int memberId, const QMap<QString, QVariant> &updatedData) {
    QString queryString = "UPDATE Members SET ";
    QStringList keys = updatedData.keys();

    for (int i = 0; i < keys.size(); ++i) {
        queryString += keys[i] + " = ?";
        if (i < keys.size() - 1) queryString += ", ";
    }

    queryString += " WHERE member_id = ?";

    QSqlQuery query;
    query.prepare(queryString);

    for (const auto &key : keys) {
        query.addBindValue(updatedData[key]);
    }

    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error updating member: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getMemberDetails(int memberId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Members WHERE member_id = ?");
    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error fetching member details: " << query.lastError().text();
    }

    return query;
}

QSqlQuery DatabaseAPI::getAllMembers() {
    QSqlQuery query("SELECT * FROM Members");

    if (!query.exec()) {
        qDebug() << "Error fetching all members: " << query.lastError().text();
    }

    return query;
}

bool DatabaseAPI::deleteMember(int memberId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Members WHERE member_id = ?");
    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error deleting member: " << query.lastError().text();
        return false;
    }

    return true;
}

// Attendance-related operations
bool DatabaseAPI::markAttendance(int memberId, const QDate &date, const QString &status) {
    QSqlQuery query;
    query.prepare("INSERT INTO Attendance (member_id, date, status) VALUES (?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(date);
    query.addBindValue(status);

    if (!query.exec()) {
        qDebug() << "Error marking attendance: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getAttendanceRecordsByMember(int memberId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Attendance WHERE member_id = ?");
    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error fetching attendance records: " << query.lastError().text();
    }

    return query;
}

QSqlQuery DatabaseAPI::getAttendanceByDate(const QDate &date) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Attendance WHERE date = ?");
    query.addBindValue(date);

    if (!query.exec()) {
        qDebug() << "Error fetching attendance by date: " << query.lastError().text();
    }

    return query;
}

// Payment-related operations
bool DatabaseAPI::addPayment(int memberId, double amount, const QDate &date, const QString &method) {
    QSqlQuery query;
    query.prepare("INSERT INTO Payments (member_id, amount, payment_date, payment_method) VALUES (?, ?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(amount);
    query.addBindValue(date);
    query.addBindValue(method);

    if (!query.exec()) {
        qDebug() << "Error adding payment: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getPaymentRecords(int memberId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Payments WHERE member_id = ?");
    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error fetching payment records: " << query.lastError().text();
    }

    return query;
}

// Class-related operations
bool DatabaseAPI::addClass(const QString &name, const QString &instructor, const QDateTime &scheduleTime) {
    QSqlQuery query;
    query.prepare("INSERT INTO Classes (class_name, instructor, schedule_time) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(instructor);
    query.addBindValue(scheduleTime);


    if (!query.exec()) {
        qDebug() << "Error adding class: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getAllClasses() {
    QSqlQuery query("SELECT * FROM Classes");

    if (!query.exec()) {
        qDebug() << "Error fetching all classes: " << query.lastError().text();
    }

    return query;
}

QSqlQuery DatabaseAPI::getClassDetails(int classId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Classes WHERE class_id = ?");
    query.addBindValue(classId);

    if (!query.exec()) {
        qDebug() << "Error fetching class details: " << query.lastError().text();
    }

    return query;
}

// Class registration-related operations
bool DatabaseAPI::registerForClass(int memberId, int classId) {
    QSqlQuery query;
    query.prepare("INSERT INTO Class_Registrations (member_id, class_id, registration_date) VALUES (?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(classId);
    query.addBindValue(QDate::currentDate()); // Using the current date for registration

    if (!query.exec()) {
        qDebug() << "Error registering for class: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getClassRegistrations(int classId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Class_Registrations WHERE class_id = ?");
    query.addBindValue(classId);

    if (!query.exec()) {
        qDebug() << "Error fetching class registrations: " << query.lastError().text();
    }

    return query;
}

// Subscription-related operations
bool DatabaseAPI::addSubscription(int memberId, const QString &type, const QString &status) {
    QSqlQuery query;
    query.prepare("INSERT INTO Subscriptions (member_id, type, status) VALUES (?, ?, ?)");
    query.addBindValue(memberId);
    query.addBindValue(type);
    query.addBindValue(status);

    if (!query.exec()) {
        qDebug() << "Error adding subscription: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseAPI::getMemberSubscriptions(int memberId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Subscriptions WHERE member_id = ?");
    query.addBindValue(memberId);

    if (!query.exec()) {
        qDebug() << "Error fetching member subscriptions: " << query.lastError().text();
    }

    return query;
}
