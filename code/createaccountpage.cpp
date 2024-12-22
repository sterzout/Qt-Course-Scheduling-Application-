#include "createaccountpage.h"
#include "ui_createaccountpage.h"
#include "coursepage.h"
#include "loginorcreate.h"

#include "student.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
createaccountpage::createaccountpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createaccountpage)
{
    ui->setupUi(this);
}

createaccountpage::~createaccountpage()
{
    delete ui;
}

void createaccountpage::on_pushButton_clicked()
{
    // set the attributes to what the user types in the textboxes
    QString name = ui->usertext->text();
    QString username = ui->usertext_2->text();
    QString email = ui->usertext_3->text();
    QString password = ui->usertext_4->text();
    //convert to std string
    std::string nameStr = name.toStdString();
    std::string usernameStr = username.toStdString();
    std::string emailStr = email.toStdString();
    std::string passwordStr = password.toStdString();

    std::ifstream file("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");
    //parse through file
    std::string line;
    bool userExists = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fileUsername, filePassword, fileEmail, fileActualPassword;
        // parse the line in order: username, password, email, actual_password
        if (std::getline(ss, fileUsername, ',') &&
            std::getline(ss, filePassword, ',') &&
            std::getline(ss, fileEmail, ',') &&
            std::getline(ss, fileActualPassword)) {

            // trim leading whitespace if any
            // trim leading and trailing whitespace
            fileUsername.erase(0, fileUsername.find_first_not_of(' '));
            fileUsername.erase(fileUsername.find_last_not_of(' ') + 1);

            filePassword.erase(0, filePassword.find_first_not_of(' '));
            filePassword.erase(filePassword.find_last_not_of(' ') + 1);

            fileEmail.erase(0, fileEmail.find_first_not_of(' '));
            fileEmail.erase(fileEmail.find_last_not_of(' ') + 1);

            fileActualPassword.erase(0, fileActualPassword.find_first_not_of(' '));
            fileActualPassword.erase(fileActualPassword.find_last_not_of(' ') + 1);

            // debugging output to confirm
            qDebug() << "Parsed Username:" << QString::fromStdString(fileUsername)
                     << ", Password:" << QString::fromStdString(fileActualPassword);

            // Check if credentials match
            if (fileUsername == name || fileActualPassword == password ||filePassword == usernameStr||fileEmail == emailStr) {
                userExists = true;
                break;
            }
        }
    }
    if (userExists){
        // if the user exists then you simply give error message else you create it successfully making a new student user.
        ui->errormessageaccount->setText("User is already taken. Unable to save account information.");
    }else{
        std::ofstream outfile("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt", std::ios::app);

        outfile << nameStr << "/"
                << usernameStr << "/"

                << emailStr << "/"
                << passwordStr << "///" << std::endl;

        outfile.close();

        ui->errormessageaccount->setText("Account created successfully!");
        //create a new student and move to coursepage to do your course stuff
        User *newUser = new User(nameStr, usernameStr, emailStr, passwordStr);
        CoursePage *nextPage = new CoursePage(newUser->createUser(nameStr, usernameStr, emailStr, passwordStr));
        this->close();
        nextPage->open();
    }

}


void createaccountpage::on_backButton_clicked()
{
    this->close();
    loginorcreate *back = new loginorcreate();
    back->show();
}

