#include "dashboard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

Dashboard::Dashboard(MemberUser *appuser, QWidget *parent) :  QWidget(parent), appuser(appuser) {

    qDebug() << "Running dashboard...";
    qDebug() << appuser->attendace;

    // Debug to check the activities list
    qDebug() << appuser->activities;

    QVBoxLayout *dashboardLayout = new QVBoxLayout(this);

    // Personalized Welcome Label
    QLabel *welcomeLabel = new QLabel("Welcome back, Firstname " + appuser->getUsername(), this);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    dashboardLayout->addWidget(welcomeLabel);

    // Membership Stats (progress bars)
    QGroupBox *progressBox = new QGroupBox("Your Membership Stats", this);
    QVBoxLayout *progressLayout = new QVBoxLayout;

    QProgressBar *attendanceProgress = new QProgressBar;
    attendanceProgress->setValue(appuser->attendace);  // Example value
    attendanceProgress->setFormat("Attendance: %p%");

    QProgressBar *goalProgress = new QProgressBar;
    goalProgress->setValue(appuser->goalProgress);  // Example value
    goalProgress->setFormat("Goal Progress: %p%");

    progressLayout->addWidget(attendanceProgress);
    progressLayout->addWidget(goalProgress);
    progressBox->setLayout(progressLayout);
    dashboardLayout->addWidget(progressBox);

    // Table for recent activity (workouts, payments, etc.)
    QTableWidget *activityTable = new QTableWidget(appuser->activities.size(), 3, this);  // Dynamically set the row count based on activities list
    activityTable->setHorizontalHeaderLabels({"Date", "Activity", "Details"});

    // Populate the activity table dynamically from appuser->activities list
    for (int i = 0; i < appuser->activities.size(); ++i) {
        QList<QString> activity = appuser->activities[i];
        activityTable->setItem(i, 0, new QTableWidgetItem(activity[0]));  // Date
        activityTable->setItem(i, 1, new QTableWidgetItem(activity[1]));  // Activity
        activityTable->setItem(i, 2, new QTableWidgetItem(activity[2]));  // Details
    }

    dashboardLayout->addWidget(activityTable);

    // Add a chart showing goal progress (e.g., weight loss)
    QPieSeries *goalSeries = new QPieSeries();
    goalSeries->append("Achieved", 75);
    goalSeries->append("Remaining", 25);

    QChart *goalChart = new QChart();
    goalChart->addSeries(goalSeries);
    goalChart->setTitle("Goal Progress");

    QChartView *goalChartView = new QChartView(goalChart);
    goalChartView->setRenderHint(QPainter::Antialiasing);
    dashboardLayout->addWidget(goalChartView);

    // Buttons for profile updates, renewal, and contact
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *updateProfileButton = new QPushButton("Update Profile", this);
    QPushButton *renewMembershipButton = new QPushButton("Renew Membership", this);
    QPushButton *contactGymButton = new QPushButton("Contact Gym", this);

    buttonLayout->addWidget(updateProfileButton);
    buttonLayout->addWidget(renewMembershipButton);
    buttonLayout->addWidget(contactGymButton);

    dashboardLayout->addLayout(buttonLayout);

    // Add spacer at the bottom to make the design more flexible
    dashboardLayout->addStretch();
    setLayout(dashboardLayout);
}
