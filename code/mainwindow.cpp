#include "mainwindow.h"
#include "coursepage.h"
#include "user.h"
#include "student.h"
#include "admin.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QDebug>
#include <string>
#include "loginorcreate.h"
#include  <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Button clicked";

    // set up boxes to input user text
    QString username = ui->usertext->text();
    QString password = ui->userpass->text();
    User* loggedInUser = validateLogin(username, password);

    if (loggedInUser) {
        //if validate login true the user is successfully passed through
        ui->errormessagebox->setText("Login successful");

        if (loggedInUser->getUserID() == "admin1") {
            //if the id is admin1, create an object of admin inherited from user.
            this->close();
            Admin* admin = new Admin(loggedInUser->getName(), loggedInUser->getUserID(),
                                     loggedInUser->getEmail(), loggedInUser->getPassword());
            CoursePage* next = new CoursePage(admin);
            next->show();
        } else {
            //else create a user object then pass this current user through to coursepage.
            this->close();
            Student* student = new Student(loggedInUser->getName(), loggedInUser->getUserID(),
                                           loggedInUser->getEmail(), loggedInUser->getPassword());
            std::string userId = student->getUserID();
            QStringList newPrerequisites = student->getCompletedCourses();
            CoursePage* next = new CoursePage(student);
            next->show();
        }
    } else {
        ui->errormessagebox->setText("Invalid username or password");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    loginorcreate *back = new loginorcreate();
    back->show();
}
User* MainWindow::validateLogin(const QString& username, const QString& password) {
    //open file if fails return nullptr
    QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->errormessagebox->setText("Error: Unable to open user data file.");
        return nullptr;
    }

    QTextStream file(&fileOpen);
    while (!file.atEnd()) {
        //if file opens we parse through and split each line to compare data for a match
        QString line = file.readLine();
        QStringList parts = line.split("/");
        if (parts.size() >= 4) {
            //only compare if parts is at least 4 split sections
            QString name = parts[0].trimmed();
            QString userID = parts[1].trimmed();
            QString email = parts[2].trimmed();
            QString passcode = parts[3].trimmed();
            std::string name1 = name.toStdString();
            std::string userID1 = userID.toStdString();
            std::string email1 = email.toStdString();
            std::string passcode1 = passcode.toStdString();

            //if there is a match we return a new user
            if (username == userID && password == passcode) {
            // debugging output to check
                qDebug() << "Parsed Username:" << (userID)
                     << ", Password:" << (passcode);
            fileOpen.close();
                return new User(name1, userID1, email1, passcode1); // create new member
            }
        }
    }

    return nullptr; // again return nullptr if no match is found
}
