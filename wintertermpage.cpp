#include "wintertermpage.h"
#include "ui_wintertermpage.h"
#include "student.h"
#include "user.h"
#include "coursepage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <string>
#include <qstring.h>
winterTermPage::winterTermPage(User* user, Course* course, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::winterTermPage)
    , currentUser(user)// initialize current user and course
    , currentCourse(course)
{
    ui->setupUi(this);
    // make all the labels such as faculty , course name and course prereqs with the for loop seperating each course
    // name by commas
    ui->courselabel->setText("Course: " + currentCourse->getCourseName());
    ui->facultylabel->setText("Faculty: " + currentCourse->getFaculty());
    ui->studentid->setText("Student ID: " + QString::fromStdString(currentUser->getUserID()));

    QString prerequisitesText = "Prerequisites: ";
    for (const QString &str : currentCourse->getPrerequisites()) {
        if (currentCourse->getPrerequisites().size()==0){
            prerequisitesText += str + "";
        }
        if (currentCourse->getPrerequisites().size()==1){
            prerequisitesText += str + "";
        }else{
            prerequisitesText += str + ", "; // Append each prerequisite followed by a comma
        }
    }
    ui->courseprereqs->setText(prerequisitesText);
}

winterTermPage::~winterTermPage()
{
    delete ui;
}

void winterTermPage::on_addCourse_clicked()
{   // add course only if student

    Student* student = dynamic_cast<Student*>(currentUser);
    qDebug() << QString::fromStdString(student->userID);


    if (student) {
        Course* course1 = new Course(currentCourse->getFaculty(),currentCourse->getCourseName(),currentCourse->getPrerequisites());
         //if student we use the student add course method for winter if it doesnt return true we cant drop the course
        if (student->addCourseToWinter(course1)){
            ui->errormessagebox->setText("Course Successfully added");
            updateStudentCourseFile(student,"Add");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);


        }else{
            ui->errormessagebox->setText("Course cannot be added due to overlapping (Course was already completed or found in current timetable)");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);

        }
    }


}


void winterTermPage::on_dropCourse_clicked()
{   // drop course only if student
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        Course* course1 = new Course(currentCourse->getFaculty(),currentCourse->getCourseName(),currentCourse->getPrerequisites());

        if (student->dropCourseFromWinter(course1)){
            //if student we use the student drop course method for winter if it doesnt return true we cant drop the course
            ui->errormessagebox->setText("Course Successfully dropped");
            updateStudentCourseFile(student,"Drop");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);


        }else{
            ui->errormessagebox->setText("Course is not in timetable");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);

        }
    }
}





void winterTermPage::updateStudentCourseFile(Student* student, std::string operation)
{
    QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");

    // open the file in read mode
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->errormessagebox->setText("Error: Unable to open user data file.");
        return;
    }

    QStringList allLines;
    QTextStream input(&fileOpen);
    // parse through until end or until the user is found by their name
    while (!input.atEnd()) {
        QString line = input.readLine();
        QStringList parts = line.split("/");

        if (parts.size() > 4) {
            if (parts[0] == student->getName()) {
                QStringList winterCourses = parts[5].split(",");
                winterCourses = student->getWinterCourses();
                parts[5] = winterCourses.join(",");
                line = parts.join("/");
                // update their courses since if they log back in it will be in the txt and we need to retrieve info
                // to reupdate their courses from the last time they were here.
            }
        }
        allLines.append(line);
    }

    fileOpen.close();

    if (!fileOpen.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        ui->errormessagebox->setText("Error: Unable to write to user data file.");
        return;
        //if file wont open return error message
    }
    QTextStream output(&fileOpen);
    for (const QString& line : allLines) {
        output << line << "\n";
    }

    fileOpen.close();
}

void winterTermPage::on_back_clicked()
{
//back to course page with same user
    this->close();
    CoursePage *goBack = new CoursePage(currentUser);
    goBack->show();

}

