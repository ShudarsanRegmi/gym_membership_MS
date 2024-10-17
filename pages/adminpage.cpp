#include "adminpage.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

AdminPage::AdminPage(DatabaseAPI *dbApi, QWidget *parent)
    : QWidget(parent), dbApi(dbApi) {
    tabWidget = new QTabWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);

    // Create user management tab
    userManagementTab = new QWidget(this);
    createUserManagementTab();

    // Create attendance report tab
    createAttendanceReportTab(); // <-- Call this method to initialize the attendance report tab

    createStatisticsTab();  // <-- Call this method to initialize the statistics tab
    tabWidget->addTab(statisticsTab, "Statistics");

    // Add tabs to the tab widget
    tabWidget->addTab(userManagementTab, "User Management");
    tabWidget->addTab(attendanceReportTab, "Attendance Report");
    tabWidget->addTab(statisticsTab, "Statistics");  // Add the statistics tab

    setLayout(mainLayout);
}

void AdminPage::createUserManagementTab() {
    QVBoxLayout *layout = new QVBoxLayout(userManagementTab);

    // Add User Button
    addUserButton = new QPushButton("Add User", userManagementTab);
    layout->addWidget(addUserButton);
    connect(addUserButton, &QPushButton::clicked, this, &AdminPage::handleAddUser);

    // User Table
    userTable = new QTableWidget(0, 5, userManagementTab);
    userTable->setHorizontalHeaderLabels({"ID", "Username", "Email", "View", "Edit"});
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(userTable);

    connect(userTable, &QTableWidget::cellClicked, this, &AdminPage::displayUserDetails);

    // Add Gym-specific details
    gymDetailsLabel = new QLabel("Gym Details for the selected user:", userManagementTab);
    layout->addWidget(gymDetailsLabel);

    // Add personal information
    personalInfoLabel = new QLabel("Personal Info for the selected user:", userManagementTab);
    layout->addWidget(personalInfoLabel);

    // Load user data into the table
    loadUserData();
}

void AdminPage::createAttendanceReportTab() {
    attendanceReportTab = new QWidget(this);  // Initialize the attendance report tab
    QVBoxLayout *layout = new QVBoxLayout(attendanceReportTab);

    // Title
    QLabel *titleLabel = new QLabel("Attendance Report", attendanceReportTab);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // Date Range Selection
    QHBoxLayout *dateLayout = new QHBoxLayout();
    QLabel *fromLabel = new QLabel("From:", attendanceReportTab);
    QDateEdit *fromDateEdit = new QDateEdit(QDate::currentDate(), attendanceReportTab);
    fromDateEdit->setCalendarPopup(true);

    QLabel *toLabel = new QLabel("To:", attendanceReportTab);
    QDateEdit *toDateEdit = new QDateEdit(QDate::currentDate(), attendanceReportTab);
    toDateEdit->setCalendarPopup(true);

    dateLayout->addWidget(fromLabel);
    dateLayout->addWidget(fromDateEdit);
    dateLayout->addWidget(toLabel);
    dateLayout->addWidget(toDateEdit);

    layout->addLayout(dateLayout);

    // Filter Button
    QPushButton *filterButton = new QPushButton("Generate Report", attendanceReportTab);
    layout->addWidget(filterButton, 0, Qt::AlignCenter);

    // Connect button to a slot (you will implement this slot)
    connect(filterButton, &QPushButton::clicked, this, [this, fromDateEdit, toDateEdit]() {
        // Generate report functionality here
        // For example, load attendance data based on selected dates
        qDebug() << "Generate report from" << fromDateEdit->date() << "to" << toDateEdit->date();
    });

    // Attendance Table
    QTableWidget *attendanceTable = new QTableWidget(0, 4, attendanceReportTab);  // 4 columns: ID, Name, Date, Status
    attendanceTable->setHorizontalHeaderLabels({"ID", "Name", "Date", "Status"});
    attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(attendanceTable);

    // Optional: Add some dummy data for demonstration
    // This will be fetched from the database later...
    attendanceTable->insertRow(0);
    attendanceTable->setItem(0, 0, new QTableWidgetItem("1"));
    attendanceTable->setItem(0, 1, new QTableWidgetItem("Subramanian Aaiyer"));
    attendanceTable->setItem(0, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(0, 3, new QTableWidgetItem("Present"));

    attendanceTable->insertRow(1);
    attendanceTable->setItem(1, 0, new QTableWidgetItem("2"));
    attendanceTable->setItem(1, 1, new QTableWidgetItem("Rashid Khan"));
    attendanceTable->setItem(1, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(1, 3, new QTableWidgetItem("Absent"));

    attendanceTable->insertRow(2);
    attendanceTable->setItem(2, 0, new QTableWidgetItem("3"));
    attendanceTable->setItem(2, 1, new QTableWidgetItem("Palinasamy"));
    attendanceTable->setItem(2, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(2, 3, new QTableWidgetItem("Absent"));

    attendanceTable->insertRow(3);
    attendanceTable->setItem(1, 0, new QTableWidgetItem("4"));
    attendanceTable->setItem(1, 1, new QTableWidgetItem("Murugan"));
    attendanceTable->setItem(1, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(1, 3, new QTableWidgetItem("Absent"));

    attendanceTable->insertRow(4);
    attendanceTable->setItem(3, 0, new QTableWidgetItem("3"));
    attendanceTable->setItem(3, 1, new QTableWidgetItem("Sanjay"));
    attendanceTable->setItem(3, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(3, 3, new QTableWidgetItem("Present"));

    attendanceTable->insertRow(5);
    attendanceTable->setItem(4, 0, new QTableWidgetItem("3"));
    attendanceTable->setItem(4, 1, new QTableWidgetItem("Harilal"));
    attendanceTable->setItem(4, 2, new QTableWidgetItem("2024-10-16"));
    attendanceTable->setItem(4, 3, new QTableWidgetItem("Present"));


    // Set the layout for the attendance report tab
    attendanceReportTab->setLayout(layout);
}

void AdminPage::createStatisticsTab() {
    statisticsTab = new QWidget(this);  // Initialize the statistics tab
    QVBoxLayout *layout = new QVBoxLayout(statisticsTab);

    // Title
    QLabel *titleLabel = new QLabel("User Statistics", statisticsTab);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // Statistical Overview
    QLabel *statOverviewLabel = new QLabel("Statistical Overview", statisticsTab);
    layout->addWidget(statOverviewLabel);

    // Sample statistics
    QLabel *totalUsersLabel = new QLabel("Total Users: 150", statisticsTab);
    QLabel *activeUsersLabel = new QLabel("Active Users: 120", statisticsTab);
    QLabel *inactiveUsersLabel = new QLabel("Inactive Users: 30", statisticsTab);

    layout->addWidget(totalUsersLabel);
    layout->addWidget(activeUsersLabel);
    layout->addWidget(inactiveUsersLabel);

    // Geographical Distribution
    QLabel *geoDistributionLabel = new QLabel("Geographical Distribution", statisticsTab);
    layout->addWidget(geoDistributionLabel);

    // Dummy geographical data (You might want to use a chart or map here)
    QTableWidget *geoTable = new QTableWidget(0, 2, statisticsTab);  // 2 columns: Location, Count
    geoTable->setHorizontalHeaderLabels({"Location", "User Count"});
    geoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(geoTable);

    // Add dummy geographical data
    QVector<QStringList> geoData = {
                                    {"New York", "50"},
                                    {"Los Angeles", "30"},
                                    {"Chicago", "20"},
                                    {"Houston", "15"},
                                    {"Phoenix", "10"},
                                    };

    for (const QStringList &data : geoData) {
        int row = geoTable->rowCount();
        geoTable->insertRow(row);
        geoTable->setItem(row, 0, new QTableWidgetItem(data[0])); // Location
        geoTable->setItem(row, 1, new QTableWidgetItem(data[1])); // User Count
    }

    // Set the layout for the statistics tab
    statisticsTab->setLayout(layout);
}


void AdminPage::loadUserData() {
    QVector<QVector<QString>> users = dbApi->getUsers();  // Retrieve all users from DB

    userTable->setRowCount(0);  // Clear table before loading

    for (int i = 0; i < users.size(); ++i) {
        userTable->insertRow(i);
        userTable->setItem(i, 0, new QTableWidgetItem(users[i][0])); // ID
        userTable->setItem(i, 1, new QTableWidgetItem(users[i][1])); // Username
        userTable->setItem(i, 2, new QTableWidgetItem(users[i][2])); // Email

        // View button
        QPushButton *viewButton = new QPushButton("View", this);
        userTable->setCellWidget(i, 3, viewButton);
        connect(viewButton, &QPushButton::clicked, [this, i]() { handleViewUser(i); });

        // Edit button
        QPushButton *editButton = new QPushButton("Edit", this);
        userTable->setCellWidget(i, 4, editButton);
        connect(editButton, &QPushButton::clicked, [this, i]() { handleEditUser(i); });
    }
}

void AdminPage::displayUserDetails(int row) {
    QString details = "ID: " + userTable->item(row, 0)->text() + "\n"
                      + "Username: " + userTable->item(row, 1)->text() + "\n"
                      + "Email: " + userTable->item(row, 2)->text();
    userDetailLabel->setText(details);

    // Get gym details from DB
    QVector<QString> gymDetails = dbApi->getUserGymDetails(userTable->item(row, 0)->text());
    gymDetailsLabel->setText("Height: " + gymDetails[0] + "\nWeight: " + gymDetails[1] + "\n...");

    // Get personal information from DBe
    QVector<QString> personalInfo = dbApi->getUserPersonalInfo(userTable->item(row, 0)->text());
    personalInfoLabel->setText("Full Name: " + personalInfo[0] + "\nFather's Name: " + personalInfo[1] + "\n...");
}

void AdminPage::handleAddUser() {
    qDebug() << "Add User functionality triggered";
}

// void AdminPage::handleViewUser(int row) {
//     QString userid = userTable->item(row, 0)->text();

//     QVector<QString> userDetails = {
//         userTable->item(row, 0)->text(),
//         userTable->item(row, 1)->text(),
//         userTable->item(row, 2)->text();
//         // Add more details as needed
//     };

//     UserViewDialog dialog(userDetails, this);
//     dialog.exec();
// }

void AdminPage::handleViewUser(int row) {
    QString userID = userTable->item(row, 0)->text();  // Get the user ID from the table

    // Fetch complete user details from dbApi using the provided userID
    QVector<QString> userDetails = dbApi->getCompleteUserInfo(userID);

    qDebug() << "Came back to handle Viewwer func..";
    qDebug() << userDetails;

    if (userDetails.isEmpty()) {
        QMessageBox::warning(this, "Error", "Unable to fetch user details.");
        return;
    }

    // Create a detailed dialog to display the user's complete info
    QDialog *userDetailsDialog = new QDialog(this);
    userDetailsDialog->setWindowTitle("User Details");
    userDetailsDialog->setMinimumSize(400, 300);  // Adjust the size as needed

    QVBoxLayout *layout = new QVBoxLayout(userDetailsDialog);

    // Add user details in a beautiful, organized way
    QLabel *titleLabel = new QLabel("<h2>User Information</h2>", userDetailsDialog);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QLabel *idLabel = new QLabel("User ID: " + userDetails[0], userDetailsDialog);
    layout->addWidget(idLabel);

    QLabel *usernameLabel = new QLabel("Username: " + userDetails[1], userDetailsDialog);
    layout->addWidget(usernameLabel);

    QLabel *emailLabel = new QLabel("Email: " + userDetails[2], userDetailsDialog);
    layout->addWidget(emailLabel);

    QLabel *fullNameLabel = new QLabel("Height " + userDetails[3], userDetailsDialog);
    layout->addWidget(fullNameLabel);

    QLabel *fatherNameLabel = new QLabel("Weight " + userDetails[4], userDetailsDialog);
    layout->addWidget(fatherNameLabel);

    QLabel *addressLabel = new QLabel("Full Name " + userDetails[5], userDetailsDialog);
    layout->addWidget(addressLabel);

    QLabel *phoneLabel = new QLabel("Father's name " + userDetails[6], userDetailsDialog);
    layout->addWidget(phoneLabel);

    QLabel *subscriptionLabel = new QLabel("Phone Number: " + userDetails[7], userDetailsDialog);
    layout->addWidget(subscriptionLabel);

    // QLabel *membershipDateLabel = new QLabel("Membership Date: " + userDetails[8], userDetailsDialog);
    // layout->addWidget(membershipDateLabel);

    // Add a close button
    QPushButton *closeButton = new QPushButton("Close", userDetailsDialog);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    connect(closeButton, &QPushButton::clicked, userDetailsDialog, &QDialog::accept);

    // Show the dialog
    userDetailsDialog->exec();
}


// void AdminPage::handleEditUser(int row) {
//     QVector<QString> userDetails = {
//         userTable->item(row, 0)->text(),
//         userTable->item(row, 1)->text(),
//         userTable->item(row, 2)->text(),
//         // Add more details as needed
//     };

void AdminPage::handleEditUser(int row) {
    QString userID = userTable->item(row, 0)->text();  // Get the user ID from the table

    // Fetch the user details from the database
    QVector<QString> userDetails = dbApi->getCompleteUserInfo(userID);

    if (userDetails.isEmpty()) {
        QMessageBox::warning(this, "Error", "Unable to fetch user details.");
        return;
    }

    // Create a dialog for editing user details
    QDialog *editDialog = new QDialog(this);
    editDialog->setWindowTitle("Edit User Details");

    QVBoxLayout *layout = new QVBoxLayout(editDialog);

    QLabel *titleLabel = new QLabel("<h2>Edit User Information</h2>", editDialog);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QLineEdit *usernameEdit = new QLineEdit(userDetails[1], editDialog); // Username
    QLineEdit *emailEdit = new QLineEdit(userDetails[2], editDialog); // Email
    QLineEdit *heightEdit = new QLineEdit(userDetails[3], editDialog); // Height
    QLineEdit *weightEdit = new QLineEdit(userDetails[4], editDialog); // Weight
    QLineEdit *fullNameEdit = new QLineEdit(userDetails[5], editDialog); // Full Name
    QLineEdit *fatherNameEdit = new QLineEdit(userDetails[6], editDialog); // Father's Name
    QLineEdit *phoneNumberEdit = new QLineEdit(userDetails[7], editDialog); // Phone Number

    // Add QLineEdits to layout
    layout->addWidget(new QLabel("Username:"));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("Email:"));
    layout->addWidget(emailEdit);
    layout->addWidget(new QLabel("Height:"));
    layout->addWidget(heightEdit);
    layout->addWidget(new QLabel("Weight:"));
    layout->addWidget(weightEdit);
    layout->addWidget(new QLabel("Full Name:"));
    layout->addWidget(fullNameEdit);
    layout->addWidget(new QLabel("Father's Name:"));
    layout->addWidget(fatherNameEdit);
    layout->addWidget(new QLabel("Phone Number:"));
    layout->addWidget(phoneNumberEdit);

    // Add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *updateButton = new QPushButton("Update", editDialog);
    QPushButton *cancelButton = new QPushButton("Cancel", editDialog);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // Handle "Cancel" button
    connect(cancelButton, &QPushButton::clicked, editDialog, &QDialog::reject);

    // Handle "Update" button
    connect(updateButton, &QPushButton::clicked, [=]() {
        // Get the updated details from the QLineEdit widgets
        QVector<QString> updatedDetails = {
            usernameEdit->text(),
            emailEdit->text(),
            heightEdit->text(),
            weightEdit->text(),
            fullNameEdit->text(),
            fatherNameEdit->text(),
            phoneNumberEdit->text()
        };

        // Update the database using dbApi
        if (dbApi->updateUserDetails(userID, updatedDetails)) {
            // Update the userTable to reflect changes
            userTable->item(row, 1)->setText(updatedDetails[0]); // Username
            userTable->item(row, 2)->setText(updatedDetails[1]); // Email

            editDialog->accept(); // Close the dialog
           QMessageBox::information(editDialog, "Update Successful", "User information was updated successfully.");
        } else {
            QMessageBox::warning(editDialog, "Error", "Failed to update user details.");
        }
    });

    // Show the dialog
    editDialog->exec();
}



//     UserEditDialog dialog(userDetails, this);
//     if (dialog.exec() == QDialog::Accepted) {
//         QVector<QString> updatedDetails = dialog.getUpdatedDetails();
//         userTable->item(row, 0)->setText(updatedDetails[0]);
//         userTable->item(row, 1)->setText(updatedDetails[1]);
//         userTable->item(row, 2)->setText(updatedDetails[2]);
//         // Update the database if needed
//     }
// }

// UserViewDialog implementation
UserViewDialog::UserViewDialog(const QVector<QString>& userDetails, QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("User Details:"));
    for (const QString& detail : userDetails) {
        layout->addWidget(new QLabel(detail));
    }
    setWindowTitle("View User");
    setLayout(layout);
}

// UserEditDialog implementation
UserEditDialog::UserEditDialog(const QVector<QString>& userDetails, QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Edit User:"));

    QLineEdit *idEdit = new QLineEdit(userDetails[0]);
    QLineEdit *usernameEdit = new QLineEdit(userDetails[1]);
    QLineEdit *emailEdit = new QLineEdit(userDetails[2]);

    layout->addWidget(new QLabel("ID:"));
    layout->addWidget(idEdit);
    layout->addWidget(new QLabel("Username:"));
    layout->addWidget(usernameEdit);
    layout->addWidget(new QLabel("Email:"));
    layout->addWidget(emailEdit);

    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, [this, idEdit, usernameEdit, emailEdit]() {
        accept();
    });

    layout->addWidget(saveButton);
    setWindowTitle("Edit User");
    setLayout(layout);
}

QVector<QString> UserEditDialog::getUpdatedDetails() {
    return { /* Add updated details here */ };
}
