#include "adminuser.h"
#include <QDebug>  // Include for displaying details

// Constructor implementation
// AdminUser::AdminUser(const QString& userid, const QString& username, const QString& email)
//     : User(userid, username, email, "admin"), userid(userid), isActive(true) {}
AdminUser::AdminUser(const QString& userid, const QString& username, const QString& email)
    : User(userid, username, email, "admin"), isActive(true) {}


// Display admin details
void AdminUser::displayDetails() const {
    qDebug() << "These details are being displayed by the admin user";
    qDebug() << "Username:" << getUsername();
    qDebug() << "Email:" << getEmail();
    qDebug() << "Role:" << getRole();
    // qDebug() << "Permissions:" << getPermissions().join(", ");
    // qDebug() << "Last Login:" << lastLogin.toString();
    qDebug() << "Account Active:" << (isActive ? "Yes" : "No");
}

// Set permissions
/*void AdminUser::setPermissions(const QStringList& newPermissions) {
    permissions = newPermissions;
}

// Get permissions
QStringList AdminUser::getPermissions() const {
    return permissions;
}

// Set last login time
void AdminUser::setLastLogin(const QDateTime& loginTime) {
    lastLogin = loginTime;
}

// Get last login time
QDateTime AdminUser::getLastLogin() const {
    return lastLogin;
}

// Set active status
void AdminUser::setActive(bool active) {
    isActive = active;
}

// Get active status
bool AdminUser::getIsActive() const {
    return isActive;
}*/
