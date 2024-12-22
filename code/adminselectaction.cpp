#include "adminselectaction.h"
#include "adminstudentaction.h"
#include "ui_adminselectaction.h"
#include "Admin.h"
#include "coursepage.h"
#include "admincoursedecision.h"

adminSelectAction::adminSelectAction(Admin* admin, QWidget* parent)
    : QDialog(parent)
    , currentUser(admin)
    , ui(new Ui::adminSelectAction)
{
    ui->setupUi(this);

    // display admin details
    if (currentUser) {
        ui->welcomeName->setText("Welcome: " + QString::fromStdString(currentUser->getName()));
        ui->userId->setText("UserID: " + QString::fromStdString(currentUser->getUserID()));
    } else {
        qDebug() << "Error: currentUser is null in adminSelectAction.";
    }
}
adminSelectAction::~adminSelectAction()
{
    delete ui;
}

void adminSelectAction::on_goCourses_clicked()
{
    adminCourseDecision *nextpage = new adminCourseDecision(currentUser);
    this->close();
    nextpage->show();
}


void adminSelectAction::on_goStudents_clicked()
{
    adminStudentAction *nextpage = new adminStudentAction(currentUser);
    this->close();
    nextpage->show();
}


void adminSelectAction::on_addConfirmCourse_2_clicked()
{
    //enter if user
    User* currentUser2 = dynamic_cast<User*>(currentUser);

    if (currentUser2){
    CoursePage *returnPage = new CoursePage(currentUser2);
    this->close();
    returnPage->show();
    }
    else{
    qDebug() << "wont cast good";
    }

}

