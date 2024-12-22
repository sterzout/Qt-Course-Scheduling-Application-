#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QStringList>

class Course
{
public:
    // constructor
    Course(const QString& faculty, const QString& courseName, const QStringList& prerequisites);

    //get faculty returns a QString, getCourseName returns QString and getPrerequisites returns a list of the course prereqs
    QString getFaculty() const;
    QString getCourseName() const;
    QStringList getPrerequisites() const;

private:
    //get constructor variables we use which are private
    QString faculty;
    QString courseName;
    QStringList prerequisites;
};

#endif // COURSE_H
