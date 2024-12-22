#include "admincoursedecision.h"
#include "ui_admincoursedecision.h"
#include "course.h"
#include "adminselectaction.h"
#include "coursecatalog.h"

adminCourseDecision::adminCourseDecision(Admin* admin,QWidget *parent)
    : QDialog(parent)
    , currentUser(admin)
    , ui(new Ui::adminCourseDecision)
    , courseCatalog(CourseCatalog::getInstance())

{
    ui->setupUi(this);
    for (Course* course: courseCatalog->getCourses()){
        qDebug() << course->getFaculty() << course->getCourseName() << course->getPrerequisites();
    }

}
adminCourseDecision::~adminCourseDecision()

{
    delete ui;
}



void adminCourseDecision::on_addConfirmCourse_clicked()
{
    QString NewcourseName = ui->courseNameEntry->text();
    QString NewFacultyName = ui->facultyNameEntry->text();
    QStringList NewCoursePrereqs = ui->coursePrerequisitesEntry->text().trimmed().split(",");

    for (QString& prereq : NewCoursePrereqs) {
        prereq = prereq.trimmed();
    }
    NewCoursePrereqs.removeAll("");


    Course *courseToAdd = new Course(NewFacultyName,NewcourseName,NewCoursePrereqs);
    AdminProxy* newBoss = new AdminProxy(currentUser);
    if (newBoss) {
        if ((newBoss->addCourse(courseToAdd))){
            ui->errorMessageBox->setText("Course Added");
            courseCatalog->addCourse(courseToAdd);
            QFile courseFile("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/courses.txt");

            // Open the file in append mode to add notifications
            if (!courseFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                qDebug() << "Error: Unable to open courses.txt for writing.";
                return;
            }

            QTextStream out(&courseFile);

            // format course + name + "has been added"
            QString course = NewFacultyName + ", " + NewcourseName + ", " + NewCoursePrereqs.join(",") ;
            if (course.endsWith(",")) {
                course = course.chopped(1); // Remove the trailing comma
            }
            out << course << "\n";

            courseFile.close();



            QFile notificationsFile("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/notifications.txt");
            // Open the file in append mode to add notifications
            if (!notificationsFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                qDebug() << "Error: Unable to open notifications.txt for writing.";
                return;
            }

            QTextStream out2(&notificationsFile);

            // format course + name + "has been added"
            QString notification = "'" + NewcourseName + "'" + " has been added in the faculty of " + NewFacultyName + "." ;
            out2 << notification << "\n";

            notificationsFile.close();
            qDebug() << "Notifications:" << notification;
            for (Course* course: courseCatalog->getCourses()){
                qDebug() << course->getFaculty() << course->getCourseName() << course->getPrerequisites();
            }

        }else{
            ui->errorMessageBox->setText("Course cannot be added");
            courseCatalog->addCourse(courseToAdd);

            }
        }else{
            ui->errorMessageBox->setText("Cannot Add Courses");
        }
}


void adminCourseDecision::on_removeConfirmCourse_clicked()
{
    QString NewcourseName = ui->courseNameEntry->text();
    QString NewFacultyName = ui->facultyNameEntry->text();

    Course *courseToRemove = new Course(NewFacultyName, NewcourseName, QStringList());
    AdminProxy* newBoss = new AdminProxy(currentUser);

    if (newBoss) {
        if ((newBoss->removeCourse(courseToRemove))) {
            ui->errorMessageBox->setText("Course removed");

            QFile coursesFile("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/courses.txt");

            if (!coursesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Error: Unable to open courses.txt for reading.";
                return;
            }

            QStringList allLines;
            QTextStream input(&coursesFile);

            // Read all lines and filter out the matching course
            while (!input.atEnd()) {
                QString line = input.readLine();
                QStringList parts = line.split(",");

                if (parts.size() > 0 && parts[0].trimmed().toLower() == NewFacultyName.trimmed().toLower() && parts[1].trimmed().toLower() == NewcourseName.trimmed().toLower()) {
                    qDebug() << "Removing course:" << line;
                    continue;
                    //skip the line so it isnt appended in updated file
                }
                allLines.append(line);
            }

            coursesFile.close();

            // open the file in write mode to overwrite it
            if (!coursesFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                qDebug() << "Error: Unable to open courses.txt for writing.";
                return;
            }

            QTextStream output(&coursesFile);

            for (const QString& line : allLines) {
                output << line << "\n";
            }

            coursesFile.close();
        } else {
            ui->errorMessageBox->setText("Cannot remove course");
        }
    } else {
        qDebug() << "Cannot complete action: AdminProxy is null.";
        ui->errorMessageBox->setText("Cannot remove course");
    }
}

void adminCourseDecision::on_back_clicked()
{

    if (currentUser) {
        // pass currentUser
        adminSelectAction* back = new adminSelectAction(currentUser);
        this->close();
        back->show();
    } else {
        qDebug() << "Error: currentUser is null.";
    }
}

