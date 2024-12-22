#include "coursetimetable.h"
#include "ui_coursetimetable.h"
#include "user.h"
#include "coursepage.h"
#include "student.h"
#include "course.h"

courseTimetable::courseTimetable(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::courseTimetable)
    , currentUser(user)
{
    ui->setupUi(this);
    ui->falltableWidget->clearContents();
    ui->wintertableWidget->clear();
    // ensure currentUser is a student type
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        // debugging output to see the current state of the course lists
        qDebug() << "Fall Courses Size:" << student->getFallCourses().size();
        qDebug() << "Winter Courses Size:" << student->getWinterCourses().size();
        qDebug() << "Fall Courses Content:" << student->getFallCourses();
        qDebug() << "Winter Courses Content:" << student->getWinterCourses();

        // display student information
        ui->identification->setText("Student ID: " + QString::fromStdString(currentUser->getUserID()));


        // populate fallterm table but also clear beforehand
        const auto& fallCourses = student->getFallCourses();
        ui->falltableWidget->setRowCount(0);
        ui->falltableWidget->setRowCount(fallCourses.size());
        ui->falltableWidget->setColumnCount(1);
        ui->falltableWidget->setHorizontalHeaderLabels(QStringList() << "Course Name");

        //fill fall table widget
        int row = 0;
        for (const QString& courseName : fallCourses) {
            QTableWidgetItem* courseNameItem = new QTableWidgetItem(courseName);
            ui->falltableWidget->setItem(row, 0, courseNameItem);
            row++;
        }

        // set column width for fall  table
        ui->falltableWidget->setColumnWidth(0, 200);
        const auto& winterCourses = student->getWinterCourses();
        ui->wintertableWidget->setRowCount(0);
        ui->wintertableWidget->setRowCount(winterCourses.size());
        ui->wintertableWidget->setColumnCount(1);
        ui->wintertableWidget->setHorizontalHeaderLabels(QStringList() << "Course Name");
        //fill winter table widget
        row = 0;
        for (const QString& courseName : winterCourses) {
            QTableWidgetItem* courseNameItem = new QTableWidgetItem(courseName);
            ui->wintertableWidget->setItem(row, 0, courseNameItem);
            row++;
        }

        // set column width for winter  table
        ui->wintertableWidget->setColumnWidth(0, 200);  // Adjust the width as necessary
    }

    // show the table
    ui->falltableWidget->show();
    ui->wintertableWidget->show();
}

courseTimetable::~courseTimetable()
{
    delete ui;
}



void courseTimetable::on_back_clicked()
{
    // go back to coursepage
    CoursePage* back = new CoursePage(currentUser);
    this->close();
    back->show();
}
