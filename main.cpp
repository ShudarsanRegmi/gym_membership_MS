#include "mainwindow.h"
#include <QApplication>
#include "databaseapi.h"
#include "./userBusinessLogic/userbusinesslogic.h"
#include "models/memberuser.h"
#include  <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the DatabaseAPI
    DatabaseAPI *dbApi = new DatabaseAPI();

    bool status = dbApi->connectToDatabase("gym_mgmt.db");

    if (status) {
        qDebug() << "Connection to the database was successful";
    } else {
        qDebug() << "Connection to the database failed";
    }

    // User *appuser = new User(0, "harekrishna", "harekrishna@gmail.com", "userr");
    MemberUser *appuser = new MemberUser("1", "haribahaadur", "harekrishna@gmail.com");
    // These further details are to be fetched from the database...
    qDebug () <<  appuser->getEmail(); // initialized..
    qDebug () << appuser->getMembershipEndDate();
    qDebug() << appuser->getDateOfBirth();
    qDebug() << appuser->getPhoneNumber();
    qDebug() << appuser->getRole(); // initialized
    qDebug() << appuser->getUserId();


    // Instantiate UserBusinessLogic and pass the DatabaseAPI instance
    UserBusinessLogic *userLogic = new UserBusinessLogic(dbApi);

    // Load all users (or relevant data) through the business logic layer
    QVector<User*> users = userLogic->loadUsers();



    // Initialize MainWindow and pass dbApi and userLogic if needed for UI interaction
    MainWindow w(appuser, dbApi);
    w.show();

    qDebug() << "main is going to terminate from here...";

    return a.exec();
}
