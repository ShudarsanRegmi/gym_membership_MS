#ifndef MEMBERUSER_H
#define MEMBERUSER_H

#include "user.h"
#include <QString>

class MemberUser : public User {
private:
    QString firstName;
    QString lastName;
    QString dateOfBirth;
    QString phoneNumber;
    QString membershipStartDate;
    QString membershipEndDate;

public:
    // MemberUser(const QString& userid, const QString& username, const QString& email, const QString& firstName, const QString& lastName,
    //            const QString& dateOfBirth, const QString& phoneNumber, const QString& membershipStartDate,
    //            const QString& membershipEndDate);
    MemberUser(const QString& userid, const QString& username, const QString& email);


    void displayDetails() const override;

    // Getters for member-specific details
    QString getFirstName() const;
    QString getLastName() const;
    QString getDateOfBirth() const;
    QString getPhoneNumber() const;
    QString getMembershipStartDate() const;
    QString getMembershipEndDate() const;
};

#endif // MEMBERUSER_H
