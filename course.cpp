#include "course.h"
//constructor
Course::Course(const QString& faculty, const QString& courseName, const QStringList& prerequisites)
    : faculty(faculty), courseName(courseName), prerequisites(prerequisites)
{
}
//getters
QString Course::getFaculty() const {
    return faculty;
}

QString Course::getCourseName() const {
    return courseName;
}

QStringList Course::getPrerequisites() const {
    return prerequisites;
}
