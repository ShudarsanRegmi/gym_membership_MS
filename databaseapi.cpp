#include "databaseapi.h"

#include "models/user.h"
#include "models/adminuser.h"
#include "models/memberuser.h"



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

// QSqlQuery DatabaseAPI::getMemberDetails(int memberId) {
//     QSqlQuery query;
//     query.prepare("SELECT * FROM Members WHERE member_id = ?");
//     query.addBindValue(memberId);

//     if (!query.exec()) {
//         qDebug() << "Error fetching member details: " << query.lastError().text();
//     }

//     return query;
// }

// first use of join

MemberDetails DatabaseAPI::getMemberDetails(int userId) {
    QSqlQuery query;
    query.prepare(
        "SELECT m.first_name, m.last_name, m.date_of_birth, m.phone_number, "
        "m.membership_start_date, m.membership_end_date "
        "FROM Members m "
        "JOIN Users u ON u.user_id = m.user_id "
        "WHERE u.user_id = ?"
        );
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "Error fetching member details: " << query.lastError().text();
        return {};  // Return an empty MemberDetails object in case of error
    }

    MemberDetails memberDetails;
    if (query.next()) {
        memberDetails.firstName = query.value("first_name").toString();
        memberDetails.lastName = query.value("last_name").toString();
        memberDetails.dateOfBirth = query.value("date_of_birth").toDate();
        memberDetails.phoneNumber = query.value("phone_number").toString();
        memberDetails.membershipStartDate = query.value("membership_start_date").toDate();
        memberDetails.membershipEndDate = query.value("membership_end_date").toDate();
    }

    return memberDetails;
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


// Admin pages uses this function...
// QVector<QVector<QString>> DatabaseAPI::getUsers() {
//     QVector<QVector<QString>> users;

//     QSqlQuery query("SELECT user_id, username, email FROM Users");
//     QString MemberUser::getPhoneNumber() const {
//         return phoneNumber;
//     }

//     while (query.next()) {
//         QVector<QString> user;
//         user.push_back(query.value(0).toString()); // user_id
//         user.push_back(query.value(1).toString()); // username
//         user.push_back(query.value(2).toString()); // email
//         users.push_back(user);
//     }

//     return users;
// }


QVector<QVector<QString>> DatabaseAPI::getUsers() {
    QVector<QVector<QString>> users;

    QSqlQuery query("SELECT user_id, username, email FROM Users");

    while (query.next()) {
        QVector<QString> user;
        user.push_back(query.value(0).toString()); // user_id
        user.push_back(query.value(1).toString()); // username
        user.push_back(query.value(2).toString()); // email
        users.push_back(user);
    }

    return users;
}

QVector<QString> DatabaseAPI::getUserGymDetails(const QString &userId) {
    QVector<QString> gymDetails;
    QSqlQuery query;
    query.prepare("SELECT height, weight, ... FROM UserGymDetails WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);
    if (query.exec()) {
        while (query.next()) {
            gymDetails.push_back(query.value(0).toString());  // Height
            gymDetails.push_back(query.value(1).toString());  // Weight
            // Add other details
        }
    }
    return gymDetails;
}
QVector<QString> DatabaseAPI::getUserPersonalInfo(const QString &userId) {
    QVector<QString> personalInfo;
    QSqlQuery query;
    query.prepare("SELECT full_name, father_name, ... FROM UserPersonalInfo WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);
    if (query.exec()) {
        while (query.next()) {
            personalInfo.push_back(query.value(0).toString());  // Full Name
            personalInfo.push_back(query.value(1).toString());  // Father's Name
            // Add other personal details
        }
    }
    return personalInfo;
}



// These methods are added later..

QVector<User*> DatabaseAPI::getAllUsers() {
    QVector<User*> users;

    QSqlQuery query;
    query.prepare("SELECT user_id, username, email, role FROM Users");

    if (query.exec()) {
        while (query.next()) {
            QString userId = query.value(0).toString();
            QString username = query.value(1).toString();
            QString email = query.value(2).toString();
            QString role = query.value(3).toString();

            qDebug() << "userid = " << userId << "username = " << username << "email = " << email << "role = " << role;

            if (role == "member") {
                // Create a MemberUser object
                qDebug() << "Here we'll update the user memebr";
                users.append(new MemberUser(userId, username, email));
            } else if (role == "admin") {
                qDebug() << "Here we'll update the admin user lists";
                // Create an AdminUser object
                users.append(new AdminUser(userId, username, email));
            }
        }
    } else {
        qDebug() << "Error fetching users:" << query.lastError().text();
    }
    qDebug() << "returning from getAllUsers dbapi";
    return users;
}
