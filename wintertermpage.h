#ifndef WINTERTERMPAGE_H
#define WINTERTERMPAGE_H
#include "course.h"
#include <QDialog>
#include "user.h"
#include "student.h"
namespace Ui {
class winterTermPage;
}

class winterTermPage : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit winterTermPage(User* user, Course* course, QWidget *parent = nullptr);
    ~winterTermPage();

private slots:
    //private methods to add drop reset schedule
    //reset is in progress
    void on_addCourse_clicked();

    void on_dropCourse_clicked();



    void on_back_clicked();
    void updateStudentCourseFile(Student* student, std::string operation);



private:
    //current user and course are used in this class
    User* currentUser;
    Course* currentCourse;
    Ui::winterTermPage *ui;
};

#endif // WINTERTERMPAGE_H
