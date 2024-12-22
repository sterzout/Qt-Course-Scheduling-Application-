#include "student.h"
#include <string>
#include "course.h"
#include "coursecatalog.h"
#include <QDebug>

Student::Student(const std::string& name, const std::string& userID, const std::string& email, const std::string& password)
    : User(name, userID, email, password), courseCatalog(CourseCatalog::getInstance()) {
}
//Qlists for list of completed courses, winter courses and fall courses
QList<QString>& Student::getCompletedCourses() {
    return studentCompletedCourses;
}
QList<QString>& Student::getWinterCourses() {
    return winterCourses;  // Return by reference
}

QList<QString>& Student::getFallCourses() {
    return fallCourses;  // Return by reference
}

bool Student::addCourseToFall(Course* course) {
    bool goodToAppend = true;
    // checks for the condition to stay true then if so it can append

    // check if course already exists in fall or winter courses
    if (fallCourses.contains(course->getCourseName()) || winterCourses.contains(course->getCourseName())) {
        goodToAppend = false;
        qDebug() << "bad";
    }

    // if not already added, check for prerequisites and completed courses
    if (goodToAppend && !studentCompletedCourses.contains(course->getCourseName())) {
        goodToAppend = true;
        qDebug() << "bad2";

        }


    // only add if goodToAppend is true and there is space in the fall courses
    if (goodToAppend && fallCourses.size() < 5) {
        fallCourses.append(course->getCourseName());
        return true;
    }else {
        return false;
        qDebug() << "bad3";

    }
}

bool Student::addCourseToWinter(Course* course) {
    bool goodToAppend = true;
    // checks for the condition to stay true then if so it can append

    // check if course already exists in fall or winter courses
    if (fallCourses.contains(course->getCourseName()) || winterCourses.contains(course->getCourseName())) {
        goodToAppend = false;
    }

    // if not already added, check for prerequisites and completed courses
    if (goodToAppend && !studentCompletedCourses.contains(course->getCourseName())) {
        goodToAppend = true;
    }

    // only add if goodToAppend is true and there is space in the winter courses
    if (goodToAppend && winterCourses.size() < 5) {
        winterCourses.append(course->getCourseName());
        return true;
    } else {
        return false;
    }
}

void Student::addCompletedCourse(Course* course) {
    bool goodToAppend = true;
    for (QString prereq : course->getPrerequisites()) {
        if (studentCompletedCourses.contains(prereq) || fallCourses.contains(prereq)|| winterCourses.contains(prereq)) {
            goodToAppend = false;
            break;
        }
    }
    if (goodToAppend){
        studentCompletedCourses.append(course->getCourseName());
    }
}

bool Student::dropCourseFromFall(Course* course) {
    //if the fall term contains the course drop all instances of it
    if (fallCourses.contains(course->getCourseName())){
        fallCourses.removeAll(course->getCourseName());
        return true;
    }
    return false;
}
bool Student::dropCourseFromWinter(Course* course) {
    //if the winter term contains the course drop all instances of it

    if (winterCourses.contains(course->getCourseName())){
        winterCourses.removeAll(course->getCourseName());
        return true;
    }
    return false;
}


