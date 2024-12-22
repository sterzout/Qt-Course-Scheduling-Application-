#include "falltermpage.h"
#include "student.h"
#include "admin.h"
#include "coursecatalog.h"
#include "coursepage.h"
#include "ui_falltermpage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QDebug>
#include <QFile>

#include <string>
#include <QDebug>
//constructor
fallTermPage::fallTermPage(User* user, Course* course, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fallTermPage)
    , currentUser(user) // initialize current user and course
    , currentCourse(course)

{
    ui->setupUi(this);
    // make all the labels such as faculty , course name and course prereqs with the for loop seperating each course
    // name by commas
    ui->coursename->setText("Course: " + currentCourse->getCourseName());
    ui->facultyname->setText("Faculty: " + currentCourse->getFaculty());
    ui->studentid->setText("Student ID" + QString::fromStdString(currentUser->userID));
    QString prerequisitesText = "Prerequisites: ";
    for (const QString &str : course->getPrerequisites()) {
        if (course->getPrerequisites().size()==0){
            prerequisitesText += str + "";
        }
        if (course->getPrerequisites().size()==1){
            prerequisitesText += str + "";
        }else{
            prerequisitesText += str + ", ";
        }
    }
    ui->courseprereqs->setText(prerequisitesText);
}
fallTermPage::~fallTermPage()
{
    delete ui;
}
void fallTermPage::on_detectbutton_clicked()
{
    // if admin list admin if student list student else its unknown since we need either student or admin of type user
    Admin* admin = dynamic_cast<Admin*>(currentUser);
    if (admin) {
        ui->detectbutton->setText("Admin");
    } else {
        Student* student = dynamic_cast<Student*>(currentUser);
        if (student) {
            ui->detectbutton->setText("Student");
        } else {
            ui->detectbutton->setText("Unknown user type");
        }
    }


}
void fallTermPage::on_addcourse_clicked()
{   // add course only if student
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        ui->detectbutton->setText("Student");
        Course* course1 = new Course(currentCourse->getFaculty(),currentCourse->getCourseName(),currentCourse->getPrerequisites());
        //if student we use the student add course method for fall if it doesnt return true we cant add the course
        if (student->addCourseToFall(course1)){
            ui->errormessagebox->setText("Course Successfully added");
            updateStudentCourseFile(student,"add");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);


        }else{
            ui->errormessagebox->setText("Course cannot be added due to overlapping (Course was already completed or found in current timetable)");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);

        }
    }
}

void fallTermPage::on_dropcourse_clicked()
{   // drop course only if student
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        Course* course1 = new Course(currentCourse->getFaculty(),currentCourse->getCourseName(),currentCourse->getPrerequisites());
        //if student we use the student drop course method for fall if it doesnt return true we cant drop the course]
        if (student->dropCourseFromFall(course1)){
            ui->errormessagebox->setText("Course Successfully dropped");
            updateStudentCourseFile(student,"remove");

            ui->errormessagebox->setAlignment(Qt::AlignCenter);


        }else{
            ui->errormessagebox->setText("Course is not in timetable");
            ui->errormessagebox->setAlignment(Qt::AlignCenter);

        }
    }
}
void fallTermPage::updateStudentCourseFile(Student* student, std::string operation)
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
                QStringList fallCourses = parts[4].split(",");
                fallCourses = student->getFallCourses();
                parts[4] = fallCourses.join(",");
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
        // cant write if the file wont open
    }
    QTextStream output(&fileOpen);
    for (const QString& line : allLines) {
        output << line << "\n";
    }

    fileOpen.close();
}



void fallTermPage::on_detectbutton_2_clicked()
{
    //detect button goes back
    this->close();
    CoursePage *goBack = new CoursePage(currentUser);
    goBack->show();
}

