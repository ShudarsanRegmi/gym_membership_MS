#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <databaseapi.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseAPI *dbApi, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget *stackedWidget;
    DatabaseAPI *dbApi;  // DatabaseAPI object for all pages


};
#endif // MAINWINDOW_H
