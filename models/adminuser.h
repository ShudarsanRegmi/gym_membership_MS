#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "user.h"
#include <QString>
#include <QDateTime>
#include <QStringList>

class AdminUser : public User {
private:
    QStringList permissions;  // List of permissions for the admin
    QDateTime lastLogin;      // Timestamp of the last login
    bool isActive;            // Indicates if the admin account is active

public:
    // AdminUser(const QString& username, const QString& email);
    AdminUser(const QString& userid, const QString& username, const QString& email);

    void displayDetails() const override;

    // Admin-specific functionality can be added here
    // void setPermissions(const QStringList& newPermissions);
    // QStringList getPermissions() const;
    // void setLastLogin(const QDateTime& loginTime);
    // QDateTime getLastLogin() const;
    // void setActive(bool active);
    // bool getIsActive() const;
};

#endif // ADMINUSER_H
