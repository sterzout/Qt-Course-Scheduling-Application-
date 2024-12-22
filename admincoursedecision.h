#ifndef ADMINCOURSEDECISION_H
#define ADMINCOURSEDECISION_H

#include <QDialog>
#include "adminproxy.h"
#include "coursecatalog.h"

namespace Ui {
class adminCourseDecision;
}

class adminCourseDecision : public QDialog
{
    Q_OBJECT

public:
    explicit adminCourseDecision(Admin* admin, QWidget *parent = nullptr);
    ~adminCourseDecision();

private slots:
    //private button methods
    void on_addConfirmCourse_clicked();
    void on_removeConfirmCourse_clicked();
    void on_back_clicked();

private:
    //variables initialized upon creation
    Admin* currentUser;
    Ui::adminCourseDecision *ui;

    CourseCatalog* courseCatalog;
};

#endif // ADMINCOURSEDECISION_H
