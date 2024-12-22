#ifndef COURSEPAGE_H
#define COURSEPAGE_H

#include <QDialog>
#include "user.h"
#include "coursecatalog.h"
#include "student.h"
namespace Ui {
class CoursePage;
}

class CoursePage : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit CoursePage(User* user, QWidget *parent = nullptr);
    ~CoursePage();

private slots:
    //all button features listed below
    void on_pushButton_clicked();
    void on_facultyComboBox_activated(int index);
    void on_CoursesComboBox_activated(int index);


    void on_falltermbutton_clicked();

    void on_adminmode_clicked();


    void on_courseCompleted_clicked();

    void on_wintertermbutton_clicked();

    void on_goToTimetable_clicked();

    void on_goToTimetable_2_clicked();

    void on_clearFallTerm_clicked();

    void on_clearWinterTerm_clicked();

    void on_goToTimetable_3_clicked();

private:
    //all private methods and variables used in the class which contain Coursepage, the current user and the course catalog
    //we pull from. the rest are methods that help us retrieve data and load data
    Ui::CoursePage *ui;
    User* currentUser;
    CourseCatalog* courseCatalog;
// singleton instance of CourseCatalog
    void loadFaculties();
    void loadCoursesByFaculty(const QString& facultyName);
    void loadCoursesFromFile(const QString& fileName);
    void loadUserCourses();
    void loadCoursesForTerm(std::ifstream& file, QList<QString>& courseList);
    void updateStudentCourseFile(Student* student);


};

#endif
