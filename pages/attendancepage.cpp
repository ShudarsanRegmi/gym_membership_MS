#include "attendancepage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
#include "./models/memberuser.h"
#include "../databaseapi.h"

AttendanceTracking::AttendanceTracking(MemberUser *appuser, DatabaseAPI *dbApi,  QWidget *parent) : QWidget(parent), appuser(appuser), dbApi(dbApi) {
    QVBoxLayout *attendanceLayout = new QVBoxLayout(this);

    // Title for the page
    QLabel *titleLabel = new QLabel("Attendance Tracking", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    attendanceLayout->addWidget(titleLabel);

    // Add a calendar widget for attendance overview
    QCalendarWidget *attendanceCalendar = new QCalendarWidget(this);
    attendanceCalendar->setGridVisible(true);
    attendanceLayout->addWidget(attendanceCalendar);

    // Button to check attendance for the selected date
    QPushButton *checkAttendanceButton = new QPushButton("Check Attendance for Selected Date", this);
    attendanceLayout->addWidget(checkAttendanceButton);

    // Table for showing filtered attendance
    QGroupBox *recentAttendanceBox = new QGroupBox("Filtered Attendance Records", this);
    QVBoxLayout *recentAttendanceLayout = new QVBoxLayout;
    QTableWidget *attendanceTable = new QTableWidget(0, 2, this);  // Placeholder row count
    attendanceTable->setHorizontalHeaderLabels({"Date", "Attendance Status"});
    // Resize columns to fit header contents
    attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    attendanceTable->horizontalHeader()->setMinimumSectionSize(50);  // Optional minimum width for better usability

    recentAttendanceLayout->addWidget(attendanceTable);
    recentAttendanceBox->setLayout(recentAttendanceLayout);
    attendanceLayout->addWidget(recentAttendanceBox);

    // Date range selection for filtering attendance
    QGroupBox *dateRangeBox = new QGroupBox("Filter Attendance by Date Range", this);
    QHBoxLayout *dateRangeLayout = new QHBoxLayout;

    QLabel *fromLabel = new QLabel("From:", this);
    QDateEdit *fromDateEdit = new QDateEdit(QDate::currentDate(), this);
    fromDateEdit->setCalendarPopup(true);

    QLabel *toLabel = new QLabel("To:", this);
    QDateEdit *toDateEdit = new QDateEdit(QDate::currentDate(), this);
    toDateEdit->setCalendarPopup(true);

    QPushButton *filterButton = new QPushButton("Filter Attendance", this);

    dateRangeLayout->addWidget(fromLabel);
    dateRangeLayout->addWidget(fromDateEdit);
    dateRangeLayout->addWidget(toLabel);
    dateRangeLayout->addWidget(toDateEdit);
    dateRangeLayout->addWidget(filterButton);
    dateRangeBox->setLayout(dateRangeLayout);
    attendanceLayout->addWidget(dateRangeBox);

    // Add a bar chart to show attendance over time
    QGroupBox *attendanceChartBox = new QGroupBox("Attendance Overview", this);
    QVBoxLayout *chartLayout = new QVBoxLayout;

    QBarSet *set0 = new QBarSet("Attendance Days");
    *set0 << 5 << 4 << 3 << 6 << 2;  // Sample data for 5 weeks

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(set0);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Weekly Attendance Overview");
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Week 1" << "Week 2" << "Week 3" << "Week 4" << "Week 5";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 7);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *chartView = new QChartView(barChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView);

    attendanceChartBox->setLayout(chartLayout);
    attendanceLayout->addWidget(attendanceChartBox);

    // Connect button to display selected date's attendance
    connect(checkAttendanceButton, &QPushButton::clicked, this, [=]() {
        QDate selectedDate = attendanceCalendar->selectedDate();
        QString userId = appuser->getUserId();

        QVector<QVector<QString>> attendanceData = dbApi->getAttendanceForDate(userId, selectedDate);
        qDebug() << "Attendace data...";
        qDebug () << attendanceData;
        populateAttendanceTable(attendanceTable, attendanceData);
    });

    // Connect button to filter attendance between two dates
    connect(filterButton, &QPushButton::clicked, this, [=]() {
        QDate fromDate = fromDateEdit->date();
        QDate toDate = toDateEdit->date();
        QString userId = appuser->getUserId();

        QVector<QVector<QString>> attendanceData = dbApi->getAttendanceBetweenDates(userId, fromDate, toDate);
        populateAttendanceTable(attendanceTable, attendanceData);
    });

    // Spacer at the bottom
    attendanceLayout->addStretch();
    setLayout(attendanceLayout);
}

// Helper function to populate the attendance table
void AttendanceTracking::populateAttendanceTable(QTableWidget *attendanceTable, const QVector<QVector<QString>> &data) {
    attendanceTable->setRowCount(data.size());
    for (int i = 0; i < data.size(); ++i) {
        attendanceTable->setItem(i, 0, new QTableWidgetItem(data[i][0]));  // Date
        attendanceTable->setItem(i, 1, new QTableWidgetItem(data[i][1]));  // Status
        // attendanceTable->setItem(i, 2, new QTableWidgetItem(data[i][2]));  // Duration
    }
}
