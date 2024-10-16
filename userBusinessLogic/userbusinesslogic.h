#ifndef USERBUSINESSLOGIC_H
#define USERBUSINESSLOGIC_H

#include "../models/user.h"
#include "../models/adminuser.h"
#include "../models/memberuser.h"
#include "../databaseapi.h"
#include <QVector>

class UserBusinessLogic {
private:
    DatabaseAPI *dbApi; // Dependency on dbApi for database operations

public:
    UserBusinessLogic(DatabaseAPI *dbApi);

    QVector<User*> loadUsers(); // Fetch all users from the database
    bool addUser(const User &user); // Add new user
    bool updateUser(const User &user); // Update existing user details
    bool removeUser(int userId); // Remove user by ID
};

#endif // USERBUSINESSLOGIC_H


// The responsibility of this layer is to fetch the data from the database as soon as the UI loads
