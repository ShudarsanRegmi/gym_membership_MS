#ifndef USER_H
#define USER_H

#include <QString>

class User {
protected:
    QString userid;
    QString username;
    QString email;
    QString role;

public:
    User(const QString& userid, const QString& username, const QString& email, const QString& role);
    virtual ~User() = default;

    // Pure virtual function - must be implemented by derived classes
    virtual void displayDetails() const = 0;

    QString getUsername() const;
    QString getEmail() const;
    QString getRole() const;
    QString getUserId() const;
};

#endif // USER_H
