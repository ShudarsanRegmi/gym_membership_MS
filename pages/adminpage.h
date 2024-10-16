#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QDateEdit>

#include "databaseapi.h"

class UserViewDialog : public QDialog {
    Q_OBJECT
public:
    explicit UserViewDialog(const QVector<QString>& userDetails, QWidget *parent = nullptr);
};

class UserEditDialog : public QDialog {
    Q_OBJECT
public:
    explicit UserEditDialog(const QVector<QString>& userDetails, QWidget *parent = nullptr);
    QVector<QString> getUpdatedDetails();
};

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(DatabaseAPI *dbApi, QWidget *parent = nullptr);

private:
    DatabaseAPI *dbApi;
    QTabWidget *tabWidget;

    // User Management Tab
    QWidget *userManagementTab;
    QWidget *attendanceReportTab;
    QTableWidget *userTable;
    QLabel *userDetailLabel;
    QLabel *gymDetailsLabel;
    QLabel *personalInfoLabel;
    QPushButton *addUserButton;
    QWidget *statisticsTab;  // Declare the statistics tab



    void createUserManagementTab();
    void createAttendanceReportTab();
    void createStatisticsTab();
    void loadUserData();
    void displayUserDetails(int row);
    void handleViewUser(int row);
    void handleEditUser(int row);

private slots:
    void handleAddUser();
};

#endif // ADMINPAGE_H
