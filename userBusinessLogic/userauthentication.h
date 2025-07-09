#ifndef USERAUTHENTICATION_H
#define USERAUTHENTICATION_H

#include <QString>

class UserAuthentication
{
public:
    UserAuthentication();
    bool callAuthenticationApi(QString &username, QString &pass);


private:
    bool authenticated;
    QString enteredUsername;
    QString enteredPass;
    QString authToken;
};

#endif // USERAUTHENTICATION_H
