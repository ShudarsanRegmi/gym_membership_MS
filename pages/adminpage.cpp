#include "adminpage.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

AdminPage::AdminPage(DatabaseAPI *dbApi, QWidget *parent) : QWidget(parent), dbApi(dbApi) {
    createUserManagementTab();
}

void AdminPage::createUserManagementTab() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add User Button
    addUserButton = new QPushButton("Add User", this);
    layout->addWidget(addUserButton);
    connect(addUserButton, &QPushButton::clicked, this, &AdminPage::handleAddUser);

    // User Table
    userTable = new QTableWidget(0, 3, this);  // 3 columns for ID, Username, Email
    userTable->setHorizontalHeaderLabels({"ID", "Username", "Email"});
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(userTable);

    connect(userTable, &QTableWidget::cellClicked, this, &AdminPage::displayUserDetails);

    // User Detail Section
    userDetailLabel = new QLabel("Select a user to view details", this);
    layout->addWidget(userDetailLabel);

    // Load user data into the table
    loadUserData();
}

void AdminPage::loadUserData() {
    QVector<QVector<QString>> users = dbApi->getUsers();  // Retrieve all users from DB

    userTable->setRowCount(0);  // Clear table before loading

    for (int i = 0; i < users.size(); ++i) {
        userTable->insertRow(i);
        userTable->setItem(i, 0, new QTableWidgetItem(users[i][0])); // ID
        userTable->setItem(i, 1, new QTableWidgetItem(users[i][1])); // Username
        userTable->setItem(i, 2, new QTableWidgetItem(users[i][2])); // Email
    }
}

void AdminPage::displayUserDetails(int row) {
    QString details = "ID: " + userTable->item(row, 0)->text() + "\n"
                      + "Username: " + userTable->item(row, 1)->text() + "\n"
                      + "Email: " + userTable->item(row, 2)->text();
    userDetailLabel->setText(details);
}

void AdminPage::handleAddUser() {
    qDebug() << "Add User functionality triggered";
}
