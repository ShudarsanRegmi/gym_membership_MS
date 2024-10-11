#include "viewsubscription.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTableWidget>
#include <QGroupBox>
#include <QDate>

ViewSubscription::ViewSubscription(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *subscriptionLayout = new QVBoxLayout(this);

    // Title for the page
    QLabel *titleLabel = new QLabel("Your Subscription Details", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    subscriptionLayout->addWidget(titleLabel);

    // Subscription details section
    QGroupBox *subscriptionBox = new QGroupBox("Current Plan Details", this);
    QVBoxLayout *subscriptionDetailsLayout = new QVBoxLayout;

    QLabel *planLabel = new QLabel("Plan: Premium Membership");
    QLabel *startDateLabel = new QLabel("Start Date: " + QDate::currentDate().toString("yyyy-MM-dd"));
    QLabel *endDateLabel = new QLabel("End Date: " + QDate::currentDate().addMonths(6).toString("yyyy-MM-dd"));
    QLabel *statusLabel = new QLabel("Status: Active");

    subscriptionDetailsLayout->addWidget(planLabel);
    subscriptionDetailsLayout->addWidget(startDateLabel);
    subscriptionDetailsLayout->addWidget(endDateLabel);
    subscriptionDetailsLayout->addWidget(statusLabel);

    subscriptionBox->setLayout(subscriptionDetailsLayout);
    subscriptionLayout->addWidget(subscriptionBox);

    // Progress bar for the days left
    QProgressBar *progressBar = new QProgressBar;
    progressBar->setValue(50);  // Assuming 50% usage for the example
    progressBar->setFormat("Days Left: %p%");
    subscriptionLayout->addWidget(progressBar);

    // Table for plan benefits
    QGroupBox *benefitsBox = new QGroupBox("Plan Benefits", this);
    QVBoxLayout *benefitsLayout = new QVBoxLayout;

    QTableWidget *benefitsTable = new QTableWidget(4, 2, this);
    benefitsTable->setHorizontalHeaderLabels({"Benefit", "Details"});
    benefitsTable->setItem(0, 0, new QTableWidgetItem("Gym Access"));
    benefitsTable->setItem(0, 1, new QTableWidgetItem("Unlimited access to all facilities"));
    benefitsTable->setItem(1, 0, new QTableWidgetItem("Personal Trainer"));
    benefitsTable->setItem(1, 1, new QTableWidgetItem("4 sessions per month"));
    benefitsTable->setItem(2, 0, new QTableWidgetItem("Classes"));
    benefitsTable->setItem(2, 1, new QTableWidgetItem("Access to all group classes"));
    benefitsTable->setItem(3, 0, new QTableWidgetItem("Swimming Pool"));
    benefitsTable->setItem(3, 1, new QTableWidgetItem("Unlimited use"));

    benefitsLayout->addWidget(benefitsTable);
    benefitsBox->setLayout(benefitsLayout);
    subscriptionLayout->addWidget(benefitsBox);

    // Action buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *renewButton = new QPushButton("Renew Subscription", this);
    QPushButton *upgradeButton = new QPushButton("Upgrade Plan", this);
    QPushButton *cancelButton = new QPushButton("Cancel Subscription", this);
    buttonLayout->addWidget(renewButton);
    buttonLayout->addWidget(upgradeButton);
    buttonLayout->addWidget(cancelButton);

    subscriptionLayout->addLayout(buttonLayout);

    // Add some padding at the bottom
    subscriptionLayout->addStretch();
    setLayout(subscriptionLayout);
}
