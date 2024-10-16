#include "user.h"

// Constructor implementation
User::User(const QString &userid, const QString& username, const QString& email, const QString& role)
    : userid(userid), username(username), email(email), role(role) {}

// Getter methods implementations
QString User::getUsername() const {
    return username;
}

QString User::getEmail() const {
    return email;
}

QString User::getRole() const {
    return role;
}

QString User::getUserId() const{
    return userid;
}
