#include "prerequisitepage.h"
#include "ui_prerequisitepage.h"
#include <qstring.h>
#include "student.h"
#include "course.h"
#include <QFile>
#include "coursepage.h"
prerequisitePage::prerequisitePage(User* user, Course* course, QWidget *parent)
    : QDialog(parent)
    , currentUser(user)
    , currentCourse(course)
    , ui(new Ui::prerequisitePage)
{
    //load in with teh prerequisites
    ui->setupUi(this);
    ui->coursename->setText(course->getCourseName());
    ui->facultyname->setText(course->getFaculty());
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

    //ensure prerequisites are not duplicates anywhere else
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student){
        if (student->getWinterCourses().contains(course->getCourseName())|| student->getFallCourses().contains(course->getCourseName())||student->getCompletedCourses().contains(course->getCourseName())){
            ui->courseavailability->setText("Course Availability: Course cannot be completed");
        }else{
            ui->courseavailability->setText("Course Availability: Course Available to complete");
        }

    }
}

prerequisitePage::~prerequisitePage()
{
    delete ui;
}

void prerequisitePage::on_addcourse_clicked()
{
    //if student add the course
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student){
        qDebug() << "before" << student->getCompletedCourses();
        if (ui->courseavailability->text() == "Course Availability: Course Available to complete" && !student->getCompletedCourses().contains(ui->coursename->text())){
            //if text says course available we add it and update the txt
            student->addCompletedCourse(currentCourse);
            qDebug() << "after" << student->getCompletedCourses();
            ui->messagebox->setText("Course Added.");
            updateStudentFile(student);
        }else{
            //else we send error message and do not add
            ui->messagebox->setText("Course not added.");
            ui->courseavailability->setText("Course Availability: Course cannot be completed");
            }
        }
}
void prerequisitePage::updateStudentFile(Student* student)
{
    QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");

    // ppen the file in read mode
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open the file for reading.";
        return;
    }

    QStringList allLines;
    QTextStream input(&fileOpen);

    // parse through the file to find the student and update their data
    while (!input.atEnd()) {
        QString line = input.readLine();
        QStringList parts = line.split("/");

        if (parts.size() > 5) {
            //find the student name
            if (parts[0] == student->getName()) {
                qDebug() << "Found student line:" << line;

                // get the completed courses and prerequisites from the file
                QStringList completedCourses = parts[6].split(",", Qt::SkipEmptyParts);
                QStringList filePrerequisites;
                if (parts.size() > 6) {
                    filePrerequisites = parts[6].split(",", Qt::SkipEmptyParts);
                }

                qDebug() << "Current completed courses from file:" << completedCourses;
                qDebug() << "Current prerequisites from file:" << filePrerequisites;

                // add the current course to completed courses if not there
                if (!completedCourses.contains(currentCourse->getCourseName())) {
                    completedCourses.append(currentCourse->getCourseName());
                    qDebug() << "Added completed course:" << currentCourse->getCourseName();
                }

                // add prerequisites from the current course if not there
                for (const QString& prereq : currentCourse->getPrerequisites()) {
                    if (!filePrerequisites.contains(prereq.trimmed())) {
                        filePrerequisites.append(prereq.trimmed());
                        qDebug() << "Added prerequisite:" << prereq;
                    }
                }

                // update the line with the new data
                parts[6] = completedCourses.join(",");
                if (parts.size() > 6) {
                    parts[6] = filePrerequisites.join(",");
                } else {
                    parts.append(filePrerequisites.join(","));
                }

                qDebug() << "Updated student line:" << parts.join("/");
            }
        }

        // add the lines back to the list of all lines
        allLines.append(parts.join("/"));
    }

    fileOpen.close();

    // open the file in write mode to save update data
    if (!fileOpen.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Error: Unable to open the file for writing.";
        return;
    }

    QTextStream output(&fileOpen);
    for (const QString& line : allLines) {
        output << line << "\n";
        //output
    }

    fileOpen.close();
    qDebug() << "Student file updated successfully.";
}





void prerequisitePage::on_backToPage_clicked()
{
    CoursePage *back = new CoursePage(currentUser);
    this->close();
    back->show();
}

