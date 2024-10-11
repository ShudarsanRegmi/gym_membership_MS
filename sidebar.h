#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    Sidebar(QWidget *parent = nullptr, QStackedWidget *stackedWidget=nullptr);

private:
    QVBoxLayout *layout;
    QPushButton *dashboardButton;
    QPushButton *membersButton;
    QPushButton *settingsButton;
    QStackedWidget *stackedWidget;
};

#endif // SIDEBAR_H
