#include "registerpage.h"
#include "databaseapi.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

RegisterPage::RegisterPage(DatabaseAPI *dbApi, QWidget *parent) : QWidget(parent), dbApi(dbApi)
{
    QLabel *titleLabel = new QLabel("User Registration", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Enter username");

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Enter password");
    passwordInput->setEchoMode(QLineEdit::Password);

    emailInput = new QLineEdit(this);
    emailInput->setPlaceholderText("Enter email");

    roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Member");
    roleComboBox->addItem("Admin");

    registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet("background-color: #007bff; color: white; padding: 10px;");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Username:", usernameInput);
    formLayout->addRow("Password:", passwordInput);
    formLayout->addRow("Email:", emailInput);
    formLayout->addRow("Role:", roleComboBox);

    QVBoxLayout *registerLayout = new QVBoxLayout(this);
    registerLayout->addWidget(titleLabel);
    registerLayout->addLayout(formLayout);
    registerLayout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterClicked);
}

void RegisterPage::onRegisterClicked()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    QString email = emailInput->text();
    QString role = roleComboBox->currentText().toLower();

    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }


    if (!dbApi->addUser(username, password, email, role)) {
        QMessageBox::critical(this, "Registration Error", "Failed to register user.");
    } else {
        QMessageBox::information(this, "Success", "User registered successfully.");
    }


}
