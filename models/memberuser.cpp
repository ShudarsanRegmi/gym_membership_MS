#include "memberuser.h"
#include <QDebug>  // Include for displaying details

// Constructor implementation
// MemberUser::MemberUser(const QString& userid, const QString& username, const QString& email, const QString& firstName,
//                        const QString& lastName, const QString& dateOfBirth, const QString& phoneNumber,
//                        const QString& membershipStartDate, const QString& membershipEndDate)
//     : User(userid, username, email, "member"), firstName(firstName), lastName(lastName),
//     dateOfBirth(dateOfBirth), phoneNumber(phoneNumber),
//     membershipStartDate(membershipStartDate), membershipEndDate(membershipEndDate) {}

MemberUser::MemberUser(const QString& userid, const QString& username, const QString& email )
    : User(userid, username, email, "member") {

    activities.append({"2024-09-15", "Workout", "Chest Day - 60 mins"});
    activities.append({"2024-09-10", "Payment", "Subscription Renewal"});
    activities.append({"2024-09-13", "Workout", "Chect Workout"});
    activities.append({"2024-09-14", "Workout", "Abs Workout"});


    qDebug() << "Executing constructor of member user function..";
    qDebug() << attendace;
    qDebug() << goalProgress;
    qDebug() << activities;
}

// Display user details
void MemberUser::displayDetails() const {
    qDebug() << "Username:" << username;
    qDebug() << "Email:" << email;
    qDebug() << "First Name:" << firstName;
    qDebug() << "Last Name:" << lastName;
    qDebug() << "Date of Birth:" << dateOfBirth;
    qDebug() << "Phone Number:" << phoneNumber;
    qDebug() << "Membership Start Date:" << membershipStartDate;
    qDebug() << "Membership End Date:" << membershipEndDate;
}

// Getters implementation
QString MemberUser::getFirstName() const {
    return firstName;
}

QString MemberUser::getLastName() const {
    return lastName;
}

QString MemberUser::getDateOfBirth() const {
    return dateOfBirth;
}

QString MemberUser::getPhoneNumber() const {
    return phoneNumber;
}

QString MemberUser::getMembershipStartDate() const {
    return membershipStartDate;
}

QString MemberUser::getMembershipEndDate() const {
    return membershipEndDate;
}
