#ifndef COURSECATALOG_H
#define COURSECATALOG_H

#include "course.h"
#include <QString>
#include <QList>

class CourseCatalog {
public:
    //singleton instance of coursecatalog since we only need one in the entire project to retrieve from
    static CourseCatalog* getInstance();
    //has method add course to the catalog and getCourses which returns QList of all courses
    void addCourse(Course* course);
    void removeCourse(Course* course);

    QList<Course*> getCourses() const;

private:
    //construct destruct
    CourseCatalog() {}
    ~CourseCatalog() {}
    // instance of course catalog and the getCourses return value
    static CourseCatalog* instance;
    QList<Course*> courses;
};

#endif
