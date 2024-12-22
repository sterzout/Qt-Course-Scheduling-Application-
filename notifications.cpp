#include "notifications.h"
#include "ui_notifications.h"
#include "coursepage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

notifications::notifications(User* user, QWidget *parent)
    : QDialog(parent)
    , currentUser(user)
    , ui(new Ui::notifications)
{
    ui->setupUi(this);

    // set up the notifications table
    ui->notifyTable->setColumnCount(1);
    ui->notifyTable->setHorizontalHeaderLabels(QStringList() << "Notifications");
    ui->notifyTable->setColumnWidth(0, 400); // Adjust the column width as needed

    // read the notifications from the file and populate table
    QFile file("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/notifications.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening notifications.txt for reading.";
        return;
    }

    QTextStream in(&file);
    QStringList lines;

    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.append(line);
    }

    file.close();

    // populate the table with the lines from the file
    ui->notifyTable->setRowCount(lines.size());

    int row = 0;
    for (const QString& line : lines) {
        QTableWidgetItem* item = new QTableWidgetItem(line);
        ui->notifyTable->setItem(row, 0, item);
        row++;
    }

    ui->notifyTable->show();
}

notifications::~notifications()
{
    delete ui;
}

void notifications::on_back_clicked()
{
    //go back to coursePage
    CoursePage *back = new CoursePage(currentUser);
    this->close();
    back->show();
}
