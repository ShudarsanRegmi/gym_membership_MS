#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <databaseapi.h>
#include "models/memberuser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MemberUser *appuser, DatabaseAPI *dbApi, QWidget *parent = nullptr);
    ~MainWindow();
    MemberUser *appuser;

private:
    QStackedWidget *stackedWidget;
    DatabaseAPI *dbApi;  // DatabaseAPI object for all pages


};
#endif // MAINWINDOW_H
