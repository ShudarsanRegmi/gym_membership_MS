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

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *dashboardLayout = new QVBoxLayout(this);

    // Personalized Welcome Label
    QLabel *welcomeLabel = new QLabel("Welcome back, Firstname Lastname", this);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    dashboardLayout->addWidget(welcomeLabel);

    // Membership Stats (progress bars)
    QGroupBox *progressBox = new QGroupBox("Your Membership Stats", this);
    QVBoxLayout *progressLayout = new QVBoxLayout;

    QProgressBar *attendanceProgress = new QProgressBar;
    attendanceProgress->setValue(65);  // Example value
    attendanceProgress->setFormat("Attendance: %p%");

    QProgressBar *goalProgress = new QProgressBar;
    goalProgress->setValue(80);  // Example value
    goalProgress->setFormat("Goal Progress: %p%");

    progressLayout->addWidget(attendanceProgress);
    progressLayout->addWidget(goalProgress);
    progressBox->setLayout(progressLayout);
    dashboardLayout->addWidget(progressBox);

    // Table for recent activity (workouts, payments, etc.)
    QTableWidget *activityTable = new QTableWidget(3, 3, this);
    activityTable->setHorizontalHeaderLabels({"Date", "Activity", "Details"});
    activityTable->setItem(0, 0, new QTableWidgetItem("2024-09-15"));
    activityTable->setItem(0, 1, new QTableWidgetItem("Workout"));
    activityTable->setItem(0, 2, new QTableWidgetItem("Chest Day - 60 mins"));
    activityTable->setItem(1, 0, new QTableWidgetItem("2024-09-10"));
    activityTable->setItem(1, 1, new QTableWidgetItem("Payment"));
    activityTable->setItem(1, 2, new QTableWidgetItem("Subscription Renewal"));

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
