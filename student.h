#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "course.h"
#include <QString>
#include <QList>
#include "coursecatalog.h"

class Student : public User {
public:
    // constructor for one of the most important classes
    Student(const std::string& name, const std::string& userID, const std::string& email, const std::string& password);
    //returns QList of strings for completed courses, winter courses and fall courses for any student.
    QList<QString>& getCompletedCourses();
    QList<QString>& getWinterCourses();

    QList<QString>& getFallCourses();

    //bool for sucess or fail to add or drop fall or winter courses.
    //add complete course will be implemented later iteration as it is not essential to the program but practical as mentioned
    //before
    bool addCourseToFall(Course* course);
    bool addCourseToWinter(Course* course);
    void addCompletedCourse(Course* course);
    bool dropCourseFromFall(Course* course);
    bool dropCourseFromWinter(Course* course);

    // user has a particular course, not really needed yet may implement later

private:
    //private variables for getters and the singleton instance of course catalog
    QStringList studentCompletedCourses;
    QStringList fallCourses;
    QStringList winterCourses;
    CourseCatalog* courseCatalog;

};

#endif
