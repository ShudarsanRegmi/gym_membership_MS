#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

class RegisterPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterPage(QWidget *parent = nullptr);

private:
    int x = 5;
};

#endif // REGISTER_H
