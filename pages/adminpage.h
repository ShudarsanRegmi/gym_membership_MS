#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>

#include "databaseapi.h"

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(DatabaseAPI *dbApi, QWidget *parent = nullptr);

private:

    DatabaseAPI *dbApi;

    QTableWidget *userTable;
    QLabel *userDetailLabel;
    QPushButton *addUserButton;

    void createUserManagementTab();
    void loadUserData();
    void displayUserDetails(int row);

private slots:
    void handleAddUser();
};

#endif // ADMINPAGE_H
