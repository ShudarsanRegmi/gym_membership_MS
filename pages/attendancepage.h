#ifndef ATTENDANCETRACKING_H
#define ATTENDANCETRACKING_H

#include "../models/memberuser.h"
#include <QTableWidget>
#include "databaseapi.h"


#include <QWidget>

class AttendanceTracking : public QWidget
{
    Q_OBJECT
public:
    explicit AttendanceTracking(MemberUser *appuser, DatabaseAPI *dbApi,  QWidget *parent = nullptr);
    void populateAttendanceTable(QTableWidget *attendanceTable, const QVector<QVector<QString>> &data);
    MemberUser *appuser;
    DatabaseAPI *dbApi;



signals:

public slots:
};

#endif // ATTENDANCETRACKING_H
