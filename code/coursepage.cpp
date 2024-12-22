#include "coursepage.h"
#include "ui_coursepage.h"
#include "loginorcreate.h"
#include "coursecatalog.h"
#include <QFile>
#include <QList>
#include "falltermpage.h"
#include "wintertermpage.h".
#include "prerequisitepage.h"
#include "studentprogresscheck.h"
#include "user.h"
#include "admin.h"
#include "student.h"
#include "adminselectaction.h"
#include <QTextStream>
#include <QDebug>
#include "course.h"
#include <fstream>
#include <sstream>
#include <QDebug>
#include <string>
#include <QDir>
#include "coursetimetable.h"
#include "notifications.h"
CoursePage::CoursePage(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CoursePage)
    , currentUser(user)
    , courseCatalog(CourseCatalog::getInstance()) //get singleton instance
{
    ui->setupUi(this);
    //print the user info
    if (currentUser) {
        ui->welcomelabel->setText("Welcome, " + QString::fromStdString(currentUser->getName()));
        ui->activeUserLabel->setText("User Active: "+ QString::fromStdString(currentUser->getUserID()));
    }
    //load the courses into the catalog, update the saved courses or new courses from previous sessions to the current logged
    //in user. also load the faculties
    loadCoursesFromFile("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/courses.txt");
    loadUserCourses();
    loadFaculties();  // Load the faculties into the combo box

}

CoursePage::~CoursePage()
{
    delete ui;
}

//back to prev page
void CoursePage::on_pushButton_clicked()
{
    loginorcreate *goback = new loginorcreate();
    goback->show();
    connect(goback, &QWidget::destroyed, goback, &QObject::deleteLater);  // Deletes goback when it's destroyed
}
//load faculties method
void CoursePage::loadFaculties()
{
    QStringList faculties;
    for (Course* course : courseCatalog->getCourses()) {
        QString faculty = course->getFaculty();
        if (!faculties.contains(faculty)) {
            faculties.append(faculty);
            qDebug() << "course: " << course->getCourseName();
        }
    }

    ui->facultyComboBox->addItems(faculties);  // Populate the combo box with faculty names
}

void CoursePage::on_facultyComboBox_activated(int index)
{
    //clicking this button/faculty combobox will list all faculties available to students
    QString selectedFaculty = ui->facultyComboBox->currentText();  // Get selected faculty
    loadCoursesByFaculty(selectedFaculty);  // Load the courses for that faculty
}

void CoursePage::loadCoursesByFaculty(const QString& facultyName)
{
    //loads the courses by the their common faculty
    QStringList courses;
    ui->CoursesComboBox->clear();
    for (Course* course : courseCatalog->getCourses()) {
        if (course->getFaculty().toLower() == facultyName.toLower()) {
            if (!courses.contains(course->getCourseName())){
                courses.append(course->getCourseName());
            }
        }
    }
    ui->CoursesComboBox->addItems(courses);

}

void CoursePage::on_CoursesComboBox_activated(int index)
{    //clicking this button/course combobox will list all course available to students in the faculty they selected before
    QString selectedCourse = ui->CoursesComboBox->currentText();  // Get selected course
    qDebug() << "Selected course: " << selectedCourse;
    for (Course* course : courseCatalog->getCourses()){
        if (course->getCourseName() == selectedCourse){
            ui->courseselectedbox->setText("Faculty: " + course->getFaculty() + "\n"+ "Course Selected: "+ selectedCourse);
        }
    }
}


void CoursePage::loadCoursesFromFile(const QString &fileName)
{
    // parses the text file and loads the courses into the course catalog
    std::ifstream file(fileName.toStdString());
    if (!file.is_open()) {
        ui->courseselectedbox->setText("Error: Unable to open course data file.");
        return;
    }

    // parse each line
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fileFaculty, fileCourse, filePrerequisites;

        // parse the line in order: faculty, course name, prerequisites
        if (std::getline(ss, fileFaculty, ',') &&
            std::getline(ss, fileCourse, ',') &&
            std::getline(ss, filePrerequisites)) {

            // Trim leading and trailing spaces
            fileFaculty.erase(0, fileFaculty.find_first_not_of(' '));
            fileFaculty.erase(fileFaculty.find_last_not_of(' ') + 1);

            fileCourse.erase(0, fileCourse.find_first_not_of(' '));
            fileCourse.erase(fileCourse.find_last_not_of(' ') + 1);

            filePrerequisites.erase(0, filePrerequisites.find_first_not_of(' '));
            filePrerequisites.erase(filePrerequisites.find_last_not_of(' ') + 1);

            // check if the prerequisites string is only "Prerequisites:"
            QString prerequisitesStr = QString::fromStdString(filePrerequisites);
            QStringList prerequisitesList;
            if (prerequisitesStr.startsWith("Prerequisites: ")) {
                prerequisitesStr = prerequisitesStr.remove("Prerequisites: ");
                prerequisitesList = prerequisitesStr.split(",", Qt::SkipEmptyParts);
                for (QString& prereq : prerequisitesList) {
                    prereq = prereq.trimmed(); // Ensure no leading or trailing spaces
                }
            } else if (prerequisitesStr == "Prerequisites:") {
                // no actual prerequisites, clear the list
                prerequisitesList.clear();
            }

            // debugging output for loaded courses
            qDebug() << "Faculty:" << QString::fromStdString(fileFaculty)
                     << ", Course Name:" << QString::fromStdString(fileCourse)
                     << ", Prerequisites:" << prerequisitesList;

            // create a new course and add it to the course catalog
            Course* course = new Course(QString::fromStdString(fileFaculty),
                                        QString::fromStdString(fileCourse),
                                        prerequisitesList);
            courseCatalog->addCourse(course);
        }
    }

    file.close();
}


void CoursePage::loadUserCourses() {
    // get the username (or userID) of the current user
    std::string currentUserID = currentUser->getUserID();  // Ensure userID is converted to std::string

    // check if courses have already been loaded for the current user
    Student* student = dynamic_cast<Student*>(currentUser);
    if (!student) {
        qDebug() << "currentUser is not a Student.";
        return;
    }

    // if courses are already loaded skip the appending
    if (!student->getFallCourses().isEmpty() || !student->getWinterCourses().isEmpty()) {
        qDebug() << "Courses already loaded.";
        return;
    }

    // open the file containing the user course data
    std::ifstream file("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/studentCourseInfo.txt");

    if (!file.is_open()) {
        qDebug() << "Unable to open courses file.";
        return;
    }

    std::string line;
    bool userFound = false;
    QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");
    //open file
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->courseselectedbox->setText("Error: Unable to open user data file.");
    } else {
        QTextStream file(&fileOpen);
        while (!file.atEnd()) {
            //while file not at end, split line by the / character
            QString line = file.readLine();
            QStringList parts = line.split("/");
            //if the split is greater than 4 which it always is, then trim the first 4 parts
            if (parts.size() > 4) {
                if (parts[0] == currentUser->name) {
                    qDebug() << "Found user: " << parts[0];

                    QString name = parts[0].trimmed();
                    QString userID = parts[1].trimmed();
                    QString email = parts[2].trimmed();
                    QString passcode = parts[3].trimmed();

                    QList<QString> preRequisites = parts;

                    qDebug() << "Name: " << name << ", UserID: " << userID << ", Email: " << email << ", Passcode: " << passcode;
                    //parse the other two parts into lists since they are fall and winter courses lists respectively
                    QStringList fallCoursesList = parts[4].split(",");
                    QStringList winterCoursesList = parts[5].split(",");
                    QStringList completedCourses = parts[6].split(",");

                    qDebug() << "Fall Courses List: " << fallCoursesList;
                    qDebug() << "Winter Courses List: " << winterCoursesList;
                    qDebug() << "Completed Courses List: " << completedCourses;

                    //remove any empty spaces
                    fallCoursesList.removeAll("");
                    winterCoursesList.removeAll("");
                    completedCourses.removeAll("");


                    // append fall courses if not already added
                    for (QString fallCourse : fallCoursesList) {
                        fallCourse = fallCourse.trimmed();
                        if (!student->getFallCourses().contains(fallCourse)) {
                            qDebug() << "Adding fall course: " << fallCourse;
                            student->getFallCourses().append(fallCourse);
                        }
                    }
                    for (QString completedCourse : completedCourses) {
                        completedCourse = completedCourse.trimmed();
                        student->getCompletedCourses().append(completedCourse);
                    }

                    // append winter courses if not already added
                    for (QString winterCourse : winterCoursesList) {
                        winterCourse = winterCourse.trimmed();
                        if (!student->getWinterCourses().contains(winterCourse)) {
                            qDebug() << "Adding winter course: " << winterCourse;
                            student->getWinterCourses().append(winterCourse);
                        }
                    }
                    //debug to confirm once more
                    qDebug() << "fall courses after update: " << student->getFallCourses();
                    qDebug() << "winter courses after update: " << student->getWinterCourses();
                    qDebug() << "completed courses after update: " << student->getCompletedCourses();

                    fileOpen.close();
                    return;
                }
            } else {
                // data format was wrong so we check with debug format
                qDebug() << "Invalid data format, skipping line.";
            }
        }
        // only if user not found
        qDebug() << "User not found in the data file.";
    }

    file.close();
}







void CoursePage::on_falltermbutton_clicked()
{   //take current course and pass throught to the fall page
    QString selectedCourse = ui->CoursesComboBox->currentText();
    qDebug() << "Selected course: " << selectedCourse;
    for (Course* course : courseCatalog->getCourses()){
        if (course->getCourseName() == selectedCourse){
            Course* course1 = new Course(course->getFaculty(),
                                         course->getCourseName(),course->getPrerequisites());
            fallTermPage *nextPage = new fallTermPage(currentUser, course1);
            this->hide();
            nextPage->show();
        }
    }
}


void CoursePage::on_adminmode_clicked()
{   // check if admin or student
    Admin* admin = dynamic_cast<Admin*>(currentUser);

    if (admin) {
        ui->adminerrormessage->setText("Admin");

        adminSelectAction *nextPage = new adminSelectAction(admin);
        this->close();
        nextPage->show();


    } else {
        Student* student = dynamic_cast<Student*>(currentUser);
        if (student) {
            ui->adminerrormessage->setText("Student");
        } else {
            ui->adminerrormessage->setText("Unknown user type");
        }
    }
}

void CoursePage::on_courseCompleted_clicked()
{   //take current course and pass throught to the course completed page, this is not an essential part of the code so we
    // will complete this full in the later iterations
    QString selectedCourse = ui->CoursesComboBox->currentText();
    qDebug() << "Selected course: " << selectedCourse;
    for (Course* course : courseCatalog->getCourses()){
        if (course->getCourseName() == selectedCourse){
            Course* course1 = new Course(course->getFaculty(),
                                         course->getCourseName(),course->getPrerequisites());
            prerequisitePage *nextPage1 = new prerequisitePage(currentUser, course1);
            this->hide();
            nextPage1->show();
        }
    }
}


void CoursePage::on_wintertermbutton_clicked()
{   //take current course and pass throught to the winter page

    QString selectedCourse = ui->CoursesComboBox->currentText();
    qDebug() << "Selected course: " << selectedCourse;
    for (Course* course : courseCatalog->getCourses()){
        if (course->getCourseName() == selectedCourse){
            Course* course1 = new Course(course->getFaculty(),
                                         course->getCourseName(),course->getPrerequisites());
            winterTermPage *nextPage = new winterTermPage(currentUser, course1);
            this->hide();
            nextPage->show();
        }
    }

}


void CoursePage::on_goToTimetable_clicked()
{
    // check current users timetable
    courseTimetable *seeTable = new courseTimetable(currentUser);
    this->hide();
    seeTable->show();
}


void CoursePage::on_goToTimetable_2_clicked()
{
    studentProgressCheck *studentCheck = new studentProgressCheck(currentUser);
    this->close();
    studentCheck->show();
}


void CoursePage::on_clearFallTerm_clicked()
{
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student){
        student->getFallCourses().clear();
        updateStudentCourseFile(student);
    }
}


void CoursePage::on_clearWinterTerm_clicked()
{
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student){
        student->getWinterCourses().clear();
        updateStudentCourseFile(student);
    }
}

void CoursePage::updateStudentCourseFile(Student* student)
{
    QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");

    // open the file in read mode
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->courseselectedbox->setText("Term Cleared");
        return;
    }

    QStringList allLines;
    QTextStream input(&fileOpen);
    // parse through until end or until the user is found by their name
    while (!input.atEnd()) {
        QString line = input.readLine();
        QStringList parts = line.split("/");

        if (parts.size() > 3) {
            if (parts[0] == student->getName()) {
                QStringList fallCourses = parts[4].split(",");
                fallCourses = student->getCompletedCourses();
                parts[4] = fallCourses.join(",");
                QStringList winterCourses = parts[5].split(",");
                winterCourses = student->getCompletedCourses();
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
        ui->courseselectedbox->setText("Term Cannot be Cleared");
        return;
        // cant write if the file wont open
    }
    QTextStream output(&fileOpen);
    for (const QString& line : allLines) {
        output << line << "\n";
    }

    fileOpen.close();
}

void CoursePage::on_goToTimetable_3_clicked()
{
    notifications *notify = new notifications(currentUser);
    this->close();
    notify->show();
}

