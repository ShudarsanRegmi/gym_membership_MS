#include "sidebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QIcon>
#include <QFrame>
#include <QDebug>



Sidebar::Sidebar(MemberUser *appuser, QWidget *parent, QStackedWidget *stackedWidget) : appuser(appuser), QWidget(parent), stackedWidget(stackedWidget) {

    qDebug() << appuser->getEmail() << appuser->getRole();

    this->setObjectName("sidebarWidget");

    QVBoxLayout *sidebarLayout = new QVBoxLayout(this);  // Set the layout directly to the Sidebar widget

    // Profile section
    QLabel *profilePic = new QLabel;
    profilePic->setPixmap(QPixmap(":/assets/images/profile.png").scaled(200, 200));
    profilePic->setAlignment(Qt::AlignCenter);

    QLabel *profileName = new QLabel(appuser->getUsername());
    profileName->setAlignment(Qt::AlignCenter);
    profileName->setStyleSheet("color: black; font-size: 14px;");

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);  // Horizontal line
    line->setFrameShadow(QFrame::Sunken);  // Shadow style for the line

    // Set the thickness and margins using style sheet
    line->setStyleSheet(
        "QFrame {"
        "  border: 2px solid black;"  // 2px thick line
        "  margin-top: 10px;"         // 10px margin at the top
        "  margin-bottom: 10px;"      // 10px margin at the bottom
        "}"
        );


    // Create buttons for the sidebar with icons
    QPushButton *homePageButton = new QPushButton("Homepage");
    homePageButton->setIcon(QIcon(":/icons/home.png"));
    homePageButton->setCursor(Qt::PointingHandCursor);

    QPushButton *dashboardButton = new QPushButton("Dashboard");
    dashboardButton->setIcon(QIcon(":/icons/dashboard.png"));
    dashboardButton->setCursor(Qt::PointingHandCursor);

    QPushButton *viewAttendanceButton = new QPushButton("View Attendance");
    viewAttendanceButton->setIcon(QIcon(":/icons/attendance.png"));
    viewAttendanceButton->setCursor(Qt::PointingHandCursor);

    QPushButton *scheduleClassesButton = new QPushButton("Schedule Classes");
    scheduleClassesButton->setIcon(QIcon(":/icons/schedule.png"));
    scheduleClassesButton->setCursor(Qt::PointingHandCursor);

    QPushButton *subscriptionButton = new QPushButton("View Your Subscription");
    subscriptionButton->setIcon(QIcon(":/icons/subscription.png"));
    subscriptionButton->setCursor(Qt::PointingHandCursor);

    QPushButton *adminPageButton = new QPushButton("Admin");
    adminPageButton->setIcon(QIcon(":/icons/admin.png"));
    adminPageButton->setCursor(Qt::PointingHandCursor);

    QPushButton *settingsPageButton = new QPushButton("Settings");
    settingsPageButton->setIcon(QIcon(":/icons/settings.png"));
    settingsPageButton->setCursor(Qt::PointingHandCursor);

    QPushButton *registerPageButton = new QPushButton("Register");
    registerPageButton->setIcon(QIcon(":/icons/register.png"));
    registerPageButton->setCursor(Qt::PointingHandCursor);

    // Add profile and buttons to the layout
    sidebarLayout->addWidget(profilePic);
    sidebarLayout->addWidget(profileName);
    sidebarLayout->addWidget(line);
    sidebarLayout->addWidget(homePageButton);
    sidebarLayout->addWidget(dashboardButton);
    sidebarLayout->addWidget(viewAttendanceButton);
    sidebarLayout->addWidget(scheduleClassesButton);
    sidebarLayout->addWidget(subscriptionButton);
    sidebarLayout->addWidget(adminPageButton);
    sidebarLayout->addWidget(settingsPageButton);
    sidebarLayout->addWidget(registerPageButton);
    sidebarLayout->addStretch();  // Pushes buttons to the top

    // Apply the layout to the sidebar
    this->setLayout(sidebarLayout);

    // Styling sidebar and buttons
    this->setStyleSheet(
        "QPushButton {"
        "  color: white;"
        "  background-color: #34495E;"
        "  padding: 10px;"
        "  border: none;"
        "  text-align: left;"
        "  font-size: 16px;"
        "  margin-bottom: 5px;"
        "  border-radius: 5px;"  // Rounded corners
        "  transition: background-color 0.3s ease;"  // Smooth transition for hover
        "}"
        "QPushButton:hover {"
        "  background-color: #1ABC9C;"
        "}"
        );

    // Connect the buttons to switch pages in the stackedWidget
    connect(homePageButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(0);  // Switch to dashboard page
    });

    connect(dashboardButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(1);  // Switch to dashboard page
    });
    connect(viewAttendanceButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(2);  // Switch to attendance page
    });
    connect(scheduleClassesButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(3);  // Switch to schedule classes page
    });
    connect(subscriptionButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(4);  // Switch to subscription page
    });
    connect(adminPageButton, &QPushButton::clicked, [=]() {
        qDebug() << "admin page button clicked";
        stackedWidget->setCurrentIndex(5);  // Switch to admin page
    });
    connect(settingsPageButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(6);  // Switch to settings page
    });
    connect(registerPageButton, &QPushButton::clicked, [=] {
        qDebug() << "register button clicked...";
        stackedWidget->setCurrentIndex(7);
    });
}


