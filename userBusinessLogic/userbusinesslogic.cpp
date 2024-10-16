#include "userbusinesslogic.h"

UserBusinessLogic::UserBusinessLogic(DatabaseAPI* dbApi) : dbApi(dbApi) {}

// QVector<User*> UserBusinessLogic::loadUsers() {
//     QVector<User*> users;

//     // Fetch data from dbApi and populate the user list
//     auto userList = dbApi->getAllUsers();

//     for (const auto& user : userList) {
//         // Use dynamic_cast to check the actual user type
//         if (AdminUser* admin = dynamic_cast<AdminUser*>(user)) {
//             // Assuming AdminUser constructor is (username, email)
//             users.append(new AdminUser(admin->getUsername(), admin->getEmail()));

//         } else if (MemberUser* member = dynamic_cast<MemberUser*>(user)) {
//             // Fetch additional member-specific details using the member's userId
//             MemberDetails memberDetails = dbApi->getMemberDetails(member->getUserId().toInt());

//             // Assuming MemberUser constructor is (userId, username, email, firstName, lastName, dateOfBirth, phoneNumber, membershipStartDate, membershipEndDate)
//             users.append(new MemberUser(
//                 member->getUserId(),                     // userId
//                 member->getUsername(),                   // username
//                 member->getEmail(),                      // email
//                 memberDetails.firstName,                 // firstName
//                 memberDetails.lastName,                  // lastName
//                 memberDetails.dateOfBirth,               // dateOfBirth
//                 memberDetails.phoneNumber,               // phoneNumber
//                 memberDetails.membershipStartDate,       // membershipStartDate
//                 memberDetails.membershipEndDate          // membershipEndDate
//                 ));
//         }
//     }

//     return users;
// }



QVector<User*> UserBusinessLogic::loadUsers() {
    qDebug() << "Business logic triggering DBApi call";
    QVector<User*> users;

    // Fetch data from dbApi and populate the user list
    auto userList = dbApi->getAllUsers();

    // for (const auto& user : userList) {
    //     // Use dynamic_cast to check the actual user type
    //     if (AdminUser* admin = dynamic_cast<AdminUser*>(user)) {
    //         // Assuming AdminUser constructor is (username, email)
    //         users.append(new AdminUser(admin->getUsername(), admin->getEmail()));

    //     } else if (MemberUser* member = dynamic_cast<MemberUser*>(user)) {
    //         // Fetch additional member-specific details using the member's userId
    //         MemberDetails memberDetails = dbApi->getMemberDetails(member->getUserId().toInt());

    //         // Assuming MemberUser constructor is (userId, username, email, firstName, lastName, dateOfBirth, phoneNumber, membershipStartDate, membershipEndDate)
    //         users.append(new MemberUser(
    //             member->getUserId(),                     // userId
    //             member->getUsername(),                   // username
    //             member->getEmail(),                      // email
    //             memberDetails.firstName,                 // firstName
    //             memberDetails.lastName,                  // lastName
    //             memberDetails.dateOfBirth,               // dateOfBirth
    //             memberDetails.phoneNumber,               // phoneNumber
    //             memberDetails.membershipStartDate,       // membershipStartDate
    //             memberDetails.membershipEndDate          // membershipEndDate
    //             ));
    //     }
    // }
    qDebug() << "Going to return from business logic";
    return userList;
}



// bool UserBusinessLogic::addUser(const User& user) {
//     // Add user to database via dbApi
//     return dbApi->addUser(user);
// }

// bool UserBusinessLogic::updateUser(const User& user) {
//     // Update user in the database
//     return dbApi->updateUser(user);
// }

// bool UserBusinessLogic::removeUser(int userId) {
//     // Remove user by ID using dbApi
//     return dbApi->removeUser(userId);
// }
