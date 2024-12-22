#include "coursecatalog.h"
#include "course.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// singleston static instance
CourseCatalog* CourseCatalog::instance = nullptr;
//getter for the singleton coursecatalog
CourseCatalog* CourseCatalog::getInstance() {
    if (instance == nullptr) {
        instance = new CourseCatalog();  // Create the singleton instance if it doesn't exist
    }
    return instance;
}

//add course
void CourseCatalog::addCourse(Course* course) {
    courses.append(course);
}
void CourseCatalog::removeCourse(Course* course){
    courses.removeAll(course);
}

//get courses from when they are loaded in with the txt. we use this to print all faculties and courses in those faculties
QList<Course*> CourseCatalog::getCourses() const {
    return courses;
}
