#include "ui_adminstudentaction.h"
#include "student.h"
#include <QString>
#include <QFile>
#include "adminstudentaction.h"
#include "adminselectaction.h"

adminStudentAction::adminStudentAction(Admin* admin, QWidget *parent)
    : QDialog(parent)
    , currentUser(admin)
    , ui(new Ui::adminStudentAction)
{
    ui->setupUi(this);

    Admin* adminUser = dynamic_cast<Admin*>(currentUser);
    if (adminUser) {
        ui->studentConfirmedMessage->setText("Hello " + QString::fromStdString(adminUser->getName()));
    } else {
        qDebug() << "Failed to cast User* to Admin.";
    }
    ui->studentTable->setColumnCount(1);
    ui->studentTable->setHorizontalHeaderLabels(QStringList() << "Notifications");
    ui->studentTable->setColumnWidth(0, 400); // Adjust the column width as needed

    // read the notifications from the file and populate the table
    QFile file("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening notifications.txt for reading.";
        return;
    }

    QTextStream in(&file);
    QStringList lines;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("/");
        lines.append("Student Name: " + parts[0] + " | Student ID: "+ parts[1]);
    }

    file.close();

    // populate the table with the lines from the file
    ui->studentTable->setRowCount(lines.size());

    int row = 0;
    for (const QString& line : lines) {
        QTableWidgetItem* item = new QTableWidgetItem(line);
        ui->studentTable->setItem(row, 0, item);
        row++;
    }

    ui->studentTable->show();
}

adminStudentAction::~adminStudentAction()
{
    delete ui;
}

void adminStudentAction::updateStudentCourseFile2(QString& studentName)
{
    AdminProxy* newBoss = new AdminProxy(currentUser);
    if (newBoss) {
        // call removeusers via adminproxy
        if (newBoss->removeUsers(studentName)) {
            ui->studentConfirmedMessage->setText("User is out of the system!");
        } else {
            ui->studentConfirmedMessage->setText("System Error!");
        }
    } else {
        qDebug() << "Cannot complete action: AdminProxy is null.";
    }
}

void adminStudentAction::on_removeStudentButton_clicked()
{
    QString studentName = ui->nameEntry->text();
    updateStudentCourseFile2(studentName);
}




void adminStudentAction::on_backButton_clicked()
{
    if (currentUser) {
        adminSelectAction* back = new adminSelectAction(currentUser);
        this->close();
        back->show();
    } else {
        qDebug() << "Error: currentUser is null.";
    }
}

