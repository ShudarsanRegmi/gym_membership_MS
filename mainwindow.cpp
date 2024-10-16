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
#include "pages/registerpage.h"
#include "pages/settingspage.h"
#include "pages/adminpage.h"

#include "databaseapi.h"


MainWindow::MainWindow(DatabaseAPI *dbApi, QWidget *parent)
    : QMainWindow(parent), dbApi(dbApi)
{
    // making database connection
    // bool status = this->dbApi->connectToDatabase("gym_mgmt.db");

    // if (status) {
    //     qDebug() << "Connection to the database was successful";
    // } else {
    //     qDebug() << "Connection to the database failed";
    // }



    // if ( dbApi->addUser("shivalal","shivalalpass","chavi@lal.com","member")) {
    //     qDebug() << "Creation of user harilal was successful...";
    // }else{
    //     qDebug() << "user creation failed";
    // }

    // if (dbApi->addUser("chandu","chandupass","chandu@lal.com","member")) {
    //     qDebug() << "Creation of user chandu was successful...";
    // }else{
    //     qDebug() << "user creation failed";
    // }


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
    RegisterPage *registerPage = new RegisterPage(dbApi);
    SettingsPage *settingsPage = new SettingsPage;
    AdminPage *adminPage = new AdminPage(dbApi);


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


    // QWidget *adminPage = new QWidget;
    // QVBoxLayout *adminPageLayout = new QVBoxLayout;
    // adminPageLayout->addWidget(new QLabel("Admin Page..."));
    // adminPage->setLayout(adminPageLayout);

    // QWidget *settingsPage = new QWidget;
    // QVBoxLayout *settingsPageLayout = new QVBoxLayout;
    // settingsPageLayout->addWidget(new QLabel("Settings Page") );

    // Add pages to stackedWidget
    stackedWidget->addWidget(homePage); //0
    stackedWidget->addWidget(dashboard); // 1
    stackedWidget->addWidget(attendanceTrackingPage); // 2
    stackedWidget->addWidget(scheduleClassPage); // 3
    stackedWidget->addWidget(viewSubscriptionPage); // 4
    stackedWidget->addWidget(adminPage); // 5
    stackedWidget->addWidget(settingsPage); // 6
    stackedWidget->addWidget(registerPage); // 7


    // Add sidebar and central widget to the main layout
    mainLayout->addWidget(sidebar);         // Sidebar on the left
    mainLayout->addWidget(stackedWidget);   // Central content area

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Gym Membership Management System");
}

MainWindow::~MainWindow() {}
