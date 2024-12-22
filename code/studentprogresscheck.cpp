#include "studentprogresscheck.h"
#include "ui_studentprogresscheck.h"
#include "user.h"
#include "coursepage.h"
studentProgressCheck::studentProgressCheck(User* user, QWidget *parent)
    : QDialog(parent)
    , currentUser(user)
    , courseCatalog(CourseCatalog::getInstance())
    , ui(new Ui::studentProgressCheck)
{
    ui->setupUi(this);
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        qDebug() << "Student object successfully casted" << student->getCompletedCourses();

        QStringList completedCourses = student->getCompletedCourses();
        int rowCount = completedCourses.size();

        ui->completedCourseTable->setRowCount(rowCount);
        ui->completedCourseTable->setColumnCount(1);

        int row = 0;
        for (const QString& course : completedCourses) {
            QTableWidgetItem* item = new QTableWidgetItem(course);
            ui->completedCourseTable->setItem(row, 0, item);
            qDebug() << "Row:" << row << ", Course Name:" << course;
            row++;
        }

        // Adjust table for display
        ui->completedCourseTable->resizeColumnsToContents();
        ui->completedCourseTable->show();
    } else {
        qDebug() << "Current user is not a Student object.";
    }
    ui->id->setText("Student ID: " + QString::fromStdString(currentUser->userID));
    ui->progressBar->setValue(0);

}


studentProgressCheck::~studentProgressCheck()
{
    delete ui;
}

void studentProgressCheck::on_addConfirmCourse_2_clicked()
{
    //load in with student knowledge and what is already completed
    CoursePage *backPage = new CoursePage(currentUser);
    this->close();
    backPage->show();
}


void studentProgressCheck::on_back_clicked()
{
    CoursePage* back = new CoursePage(currentUser);
    this->close();
    back->show();
}

void studentProgressCheck::on_calculateProgress_clicked()
{
    Student* student = dynamic_cast<Student*>(currentUser);
    if (student) {
        bool degreeExist = false;

        // Ensure user input is processed properly (lowercase, trimmed)
        QString enteredDegree = ui->degreeEntry->text().toLower();
        qDebug() << "Entered Degree:" << enteredDegree;

        // Check if the entered degree exists in the course catalog
        for (Course* course : courseCatalog->getCourses()) {
            QString facultyName = course->getFaculty().toLower(); // Standardize case and trim whitespace
            qDebug() << "Checking Faculty: Entered Degree:" << enteredDegree << ", Course Faculty:" << facultyName;
            if (enteredDegree == facultyName) {
                degreeExist = true;
                break;
            }
        }

        // validate totalCreditsEntry is an integer and greater than 0
        bool ok;
        int totalCredits = ui->totalCreditsEntry->text().toInt(&ok);

        if (!degreeExist) {
            ui->errorMessageBox->setText("Degree does not exist! Please enter a valid degree.");
            qDebug() << "Degree not found!";
            ui->resultOutcome->setText("");
            ui->progressBar->setValue(0);


        } else if (!ok || totalCredits <= student->getCompletedCourses().size()) {
            // check if the input is not an integer or less than or equal to completed courses
            ui->errorMessageBox->setText("Invalid total credits entry! Please enter a valid number greater than your completed credits.");
            qDebug() << "Invalid total credits entry.";
            ui->resultOutcome->setText("");
            //set progress to 0 for any failures
            ui->progressBar->setValue(0);


        } else {
            // clear error message in case next input true
            ui->errorMessageBox->setText("");

            // calculate progress
            //convert to string and ensure the int conversion works too
            int completedCredits = student->getCompletedCourses().size();
            int calculation = (completedCredits * 100) / totalCredits;
            QString calculationString = QString::number(calculation);
            ui->resultOutcome->setText(calculationString + "%" + " of your " + ui->degreeEntry->text() + " Degree is Complete! Keep it up!");
            ui->progressBar->setValue(calculation);
            // debugging output and progress bar set to match degree completion
            qDebug() << "Degree exists and total credits are valid.";
            qDebug() << "Total Credits:" << totalCredits;
            qDebug() << "Completed Credits:" << completedCredits;
            qDebug() << "Progress Calculation:" << calculationString + "%";
        }
    }
}
