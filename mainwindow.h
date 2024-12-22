#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string> // Required for std::string
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // login or go back
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:

    Ui::MainWindow *ui;
    //validate login simply goes through userinfo file to find valid login credentials either rejects or accepts
    User* validateLogin(const QString& username, const QString& password); // Updated return type
};

#endif // MAINWINDOW_H
