#include "loginorcreate.h"
#include "ui_loginorcreate.h"
#include "mainwindow.h"
#include "createaccountpage.h"

loginorcreate::loginorcreate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginorcreate)
{
    ui->setupUi(this);
}
//login or create simple class which navigates to either starter menu
loginorcreate::~loginorcreate()
{
    delete ui;
}

void loginorcreate::on_loginbutton_clicked()
{
    this->hide();
    MainWindow *nextWindow = new MainWindow(this);
    nextWindow->show();
}


void loginorcreate::on_createbutton_clicked()
{
    this->hide();
    createaccountpage *nextpage = new createaccountpage(this);
    nextpage->show();
}



void loginorcreate::on_programexitbutton_clicked()
{
    QApplication::quit();
}

