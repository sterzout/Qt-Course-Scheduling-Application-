#ifndef ADMINSTUDENTACTION_H
#define ADMINSTUDENTACTION_H

#include <QDialog>
#include "user.h"
#include "student.h"
#include "adminproxy.h"
namespace Ui {
class adminStudentAction;
}

class adminStudentAction : public QDialog
{
    Q_OBJECT

public:
    explicit adminStudentAction(Admin* admin, QWidget *parent = nullptr);
    ~adminStudentAction();

private slots:
    void updateStudentCourseFile2(QString& studentName);


    void on_removeStudentButton_clicked();



    void on_backButton_clicked();

private:
    Admin* currentUser;
    Ui::adminStudentAction *ui;
};

#endif // ADMINSTUDENTACTION_H
