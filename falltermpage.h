#ifndef FALLTERMPAGE_H
#define FALLTERMPAGE_H

#include <QDialog>
#include "user.h"

#include "course.h"
#include "coursecatalog.h"
#include "student.h"

namespace Ui {
class fallTermPage;
}

class fallTermPage : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit fallTermPage(User* user, Course* course, QWidget *parent = nullptr);
    //takes use and that course being looked at into the fall term page
    ~fallTermPage();

private slots:
    // only important thing here is that you either drop or add the course, there are methods in student class to handle cases
    void on_detectbutton_clicked();

    void on_addcourse_clicked();

    void on_dropcourse_clicked();

    void on_detectbutton_2_clicked();
    void updateStudentCourseFile(Student* student, std::string operation);


private:
    //current user and the cours being viewed
    User* currentUser;
    Course* currentCourse;
    Ui::fallTermPage *ui;

};

#endif // FALLTERMPAGE_H
