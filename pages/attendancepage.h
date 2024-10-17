#ifndef ATTENDANCETRACKING_H
#define ATTENDANCETRACKING_H

#include "../models/memberuser.h"


#include <QWidget>

class AttendanceTracking : public QWidget
{
    Q_OBJECT
public:
    explicit AttendanceTracking(MemberUser *appuser,  QWidget *parent = nullptr);
    MemberUser *appuser;


signals:

public slots:
};

#endif // ATTENDANCETRACKING_H
