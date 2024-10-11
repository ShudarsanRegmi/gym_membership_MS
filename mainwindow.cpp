#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "sidebar.h"

#include "pages/homepage.h"
#include "pages/dashboard.h"
#include "pages/attendancepage.h"
#include "pages/viewsubscription.h"
#include "pages/scheduleclasspaage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;


    stackedWidget = new QStackedWidget;
    Sidebar *sidebar = new Sidebar(this, stackedWidget);  // Pass 'this' as the parent

    // Create pages (widgets)
    // QWidget *dashboardPage = new QWidget;
    // QVBoxLayout *dashboardLayout = new QVBoxLayout;
    // dashboardLayout->addWidget(new QLabel("Dashboard Page"));
    // dashboardPage->setLayout(dashboardLayout);

    // // Create a new instance of DashboardPage
    // DashboardPage *dashboardPage = new DashboardPage;
    // stackedWidget->addWidget(dashboardPage);


    // QWidget *homePage = new QWidget;
    // QVBoxLayout *homePageLayout = new QVBoxLayout;
    // homePageLayout->addWidget(new QLabel("Homepage"));
    // homePage->setLayout(homePageLayout);

    Homepage *homePage = new Homepage;
    Dashboard *dashboard = new Dashboard;
    AttendanceTracking *attendanceTrackingPage = new AttendanceTracking;
    ViewSubscription *viewSubscriptionPage = new ViewSubscription;
    ScheduleClasses *scheduleClassPage = new ScheduleClasses;


    // QWidget *studentsPage = new QWidget;
    // QVBoxLayout *studentsLayout = new QVBoxLayout;
    // studentsLayout->addWidget(new QLabel("Students Management Page"));
    // studentsPage->setLayout(studentsLayout);

    // QWidget


    // QWidget *attendaceTrackingPage = new QWidget;
    // QVBoxLayout *attendanceTrackingLayout = new QVBoxLayout;
    // attendanceTrackingLayout->addWidget(new QLabel("Attendace Tracking Page"));
    // attendaceTrackingPage->setLayout(attendanceTrackingLayout);


    // QWidget *scheduleClassPage = new QWidget;
    // QVBoxLayout *scheduleClassLayout = new QVBoxLayout;
    // scheduleClassLayout->addWidget(new QLabel("Schedule Page"));
    // scheduleClassPage->setLayout(scheduleClassLayout);


    QWidget *adminPage = new QWidget;
    QVBoxLayout *adminPageLayout = new QVBoxLayout;
    adminPageLayout->addWidget(new QLabel("Admin Page..."));
    adminPage->setLayout(adminPageLayout);

    QWidget *settingsPage = new QWidget;
    QVBoxLayout *settingsPageLayout = new QVBoxLayout;
    settingsPageLayout->addWidget(new QLabel("Settings Page") );

    // Add pages to stackedWidget
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(dashboard);
    stackedWidget->addWidget(attendanceTrackingPage);
    stackedWidget->addWidget(scheduleClassPage);
    stackedWidget->addWidget(viewSubscriptionPage);
    stackedWidget->addWidget(adminPage);
    stackedWidget->addWidget(settingsPage);

    // Add sidebar and central widget to the main layout
    mainLayout->addWidget(sidebar);         // Sidebar on the left
    mainLayout->addWidget(stackedWidget);   // Central content area

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Gym Membership Management System");
}

MainWindow::~MainWindow() {}
