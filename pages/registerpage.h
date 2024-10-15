#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <databaseapi.h>

class RegisterPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterPage(DatabaseAPI *dbApi, QWidget *parent = nullptr);

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *emailInput;
    QComboBox *roleComboBox;
    QPushButton *registerButton;
    DatabaseAPI *dbApi;



private slots:
    void onRegisterClicked();
};

#endif // REGISTERPAGE_H
