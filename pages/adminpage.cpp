#include "adminpage.h"

#include <QLabel>
#include <QVBoxLayout>

AdminPage::AdminPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *adminPageLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("this is my admin page...");

    adminPageLayout->addWidget(label);

}
