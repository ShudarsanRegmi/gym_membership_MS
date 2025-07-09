#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include "models/memberuser.h"


class Dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit Dashboard(MemberUser *appuser, QWidget *parent = nullptr);
    MemberUser *appuser;
};

#endif // DASHBOARD_H
