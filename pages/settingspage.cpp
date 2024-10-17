#include "settingspage.h"


#include <QLabel>
#include <QVBoxLayout>

// settingsPage::settingsPage() {}

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout *settingsPageLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Future Work: Features to be implemented: Theme, Data Export, Language settings, Font settings, etc.", this);

    settingsPageLayout->addWidget(label);
}
