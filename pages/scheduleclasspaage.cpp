#include "scheduleclasspaage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QDateEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QGroupBox>

ScheduleClasses::ScheduleClasses(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *scheduleLayout = new QVBoxLayout(this);

    // Title for the page
    QLabel *titleLabel = new QLabel("Schedule Classes", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    scheduleLayout->addWidget(titleLabel);

    // GroupBox for class selection
    QGroupBox *classSelectionBox = new QGroupBox("Class Selection", this);
    QVBoxLayout *classSelectionLayout = new QVBoxLayout;

    // Calendar to select the date
    QLabel *dateLabel = new QLabel("Select Class Date:");
    QCalendarWidget *calendar = new QCalendarWidget(this);
    classSelectionLayout->addWidget(dateLabel);
    classSelectionLayout->addWidget(calendar);

    // Dropdown for selecting class type
    QLabel *classTypeLabel = new QLabel("Select Class Type:");
    QComboBox *classTypeComboBox = new QComboBox(this);
    classTypeComboBox->addItems({"Yoga", "Zumba", "Strength Training", "Cardio", "Swimming"});
    classSelectionLayout->addWidget(classTypeLabel);
    classSelectionLayout->addWidget(classTypeComboBox);

    // Dropdown for selecting instructor
    QLabel *instructorLabel = new QLabel("Select Instructor:");
    QComboBox *instructorComboBox = new QComboBox(this);
    instructorComboBox->addItems({"John Smith", "Jane Doe", "Alex Johnson", "Emily Williams"});
    classSelectionLayout->addWidget(instructorLabel);
    classSelectionLayout->addWidget(instructorComboBox);

    classSelectionBox->setLayout(classSelectionLayout);
    scheduleLayout->addWidget(classSelectionBox);

    // Action buttons to schedule or cancel a class
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *scheduleButton = new QPushButton("Schedule Class", this);
    QPushButton *cancelButton = new QPushButton("Cancel Class", this);
    buttonLayout->addWidget(scheduleButton);
    buttonLayout->addWidget(cancelButton);
    scheduleLayout->addLayout(buttonLayout);

    // GroupBox for viewing scheduled classes
    QGroupBox *scheduledClassesBox = new QGroupBox("Your Scheduled Classes", this);
    QVBoxLayout *scheduledClassesLayout = new QVBoxLayout;

    // Table for viewing scheduled classes
    QTableWidget *classesTable = new QTableWidget(5, 4, this);
    classesTable->setHorizontalHeaderLabels({"Class Type", "Instructor", "Date", "Time"});
    classesTable->setItem(0, 0, new QTableWidgetItem("Yoga"));
    classesTable->setItem(0, 1, new QTableWidgetItem("John Smith"));
    classesTable->setItem(0, 2, new QTableWidgetItem("2024-09-18"));
    classesTable->setItem(0, 3, new QTableWidgetItem("10:00 AM"));

    classesTable->setItem(1, 0, new QTableWidgetItem("Zumba"));
    classesTable->setItem(1, 1, new QTableWidgetItem("Jane Doe"));
    classesTable->setItem(1, 2, new QTableWidgetItem("2024-09-20"));
    classesTable->setItem(1, 3, new QTableWidgetItem("12:00 PM"));

    scheduledClassesLayout->addWidget(classesTable);
    scheduledClassesBox->setLayout(scheduledClassesLayout);
    scheduleLayout->addWidget(scheduledClassesBox);

    // Search functionality to find specific classes
    QGroupBox *searchBox = new QGroupBox("Search Classes", this);
    QVBoxLayout *searchLayout = new QVBoxLayout;
    QLineEdit *searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Search by class type or instructor...");
    searchLayout->addWidget(searchBar);
    searchBox->setLayout(searchLayout);
    scheduleLayout->addWidget(searchBox);

    // Add some padding at the bottom
    scheduleLayout->addStretch();
    setLayout(scheduleLayout);
}
