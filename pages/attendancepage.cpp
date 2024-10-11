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

AttendanceTracking::AttendanceTracking(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *attendanceLayout = new QVBoxLayout(this);

    // Title for the page
    QLabel *titleLabel = new QLabel("Attendance Tracking", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    attendanceLayout->addWidget(titleLabel);

    // Add a calendar widget for attendance overview
    QCalendarWidget *attendanceCalendar = new QCalendarWidget(this);
    attendanceCalendar->setGridVisible(true);
    attendanceLayout->addWidget(attendanceCalendar);

    // Recent attendance table
    QGroupBox *recentAttendanceBox = new QGroupBox("Recent Attendance Records", this);
    QVBoxLayout *recentAttendanceLayout = new QVBoxLayout;

    QTableWidget *attendanceTable = new QTableWidget(5, 3, this);
    attendanceTable->setHorizontalHeaderLabels({"Date", "Attendance Status", "Duration (mins)"});
    attendanceTable->setItem(0, 0, new QTableWidgetItem("2024-09-10"));
    attendanceTable->setItem(0, 1, new QTableWidgetItem("Present"));
    attendanceTable->setItem(0, 2, new QTableWidgetItem("60"));
    attendanceTable->setItem(1, 0, new QTableWidgetItem("2024-09-09"));
    attendanceTable->setItem(1, 1, new QTableWidgetItem("Absent"));
    attendanceTable->setItem(2, 0, new QTableWidgetItem("2024-09-08"));
    attendanceTable->setItem(2, 1, new QTableWidgetItem("Present"));
    attendanceTable->setItem(2, 2, new QTableWidgetItem("45"));

    recentAttendanceLayout->addWidget(attendanceTable);
    recentAttendanceBox->setLayout(recentAttendanceLayout);
    attendanceLayout->addWidget(recentAttendanceBox);

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

    // Search bar and filters
    QGroupBox *filterBox = new QGroupBox("Filter Attendance", this);
    QVBoxLayout *filterLayout = new QVBoxLayout;

    QLineEdit *searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Search attendance by date...");
    QComboBox *filterCombo = new QComboBox;
    filterCombo->addItems({"All", "Present", "Absent"});

    filterLayout->addWidget(searchBar);
    filterLayout->addWidget(filterCombo);
    filterBox->setLayout(filterLayout);
    attendanceLayout->addWidget(filterBox);

    // Add a "Mark Attendance" button
    QPushButton *markAttendanceButton = new QPushButton("Mark Today's Attendance", this);
    attendanceLayout->addWidget(markAttendanceButton);

    // Spacer at the bottom
    attendanceLayout->addStretch();
    setLayout(attendanceLayout);
}
