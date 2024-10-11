#include "registerpage.h"

#include <QLabel>
#include <QVBoxLayout>

RegisterPage::RegisterPage(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("this is register page", this);

    QVBoxLayout *registerLayout = new QVBoxLayout(this);

    registerLayout->addWidget(label);

}
