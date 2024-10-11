#include "settingspage.h"


#include <QLabel>
#include <QVBoxLayout>

// settingsPage::settingsPage() {}

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout *settingsPageLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("this is settings page..", this);

    settingsPageLayout->addWidget(label);
}
