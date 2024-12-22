#ifndef ADMINPROXY_H
#define ADMINPROXY_H

#include "admin.h"
#include "coursecatalog.h"
#include <QString>
#include "QIODevice"
#include <QFile>
#include <QDebug>

class AdminProxy {
public:
    // constructor
    AdminProxy(Admin* admin) : admin(admin) {}

    virtual ~AdminProxy() {}

    // methods to control access to admin methods
    // add a course
    bool addCourse(Course* course) {
        if (!hasAdminAccess()) {
            qDebug() << "Access denied. Admin privileges required.";
            return false;
        }

        // Check if the course already exists in the catalog
        for (Course* courseIndex : CourseCatalog::getInstance()->getCourses()) {
            if (courseIndex->getCourseName().toLower() == course->getCourseName().toLower()) {
                qDebug() << "Course already exists in catalog: " << course->getCourseName();
                return false;
            }
        }

        // Check if the faculty exists
        for (Course* courseIndex : CourseCatalog::getInstance()->getCourses()) {
            if (courseIndex->getFaculty().toLower() == course->getFaculty().toLower()) {
                return true;
            }
        }
        return false;

    }


    // remove a course
    bool removeCourse(Course* course) {
        if (hasAdminAccess()) {
            qDebug() << "Attempting to remove course:" << course->getCourseName();

            // go over courses to find a match
            for (Course* courseIndex : CourseCatalog::getInstance()->getCourses()) {
                if (courseIndex->getCourseName().toLower() == course->getCourseName().toLower() && courseIndex->getFaculty().toLower() == course->getFaculty().toLower()) {
                    CourseCatalog::getInstance()->removeCourse(courseIndex); // Remove existing course
                    qDebug() << "Course removed successfully.";
                    return true;
                }
            }
            // indicates failure
            qDebug() << "Course not found in catalog.";
            return false;
        } else {
            qDebug() << "Access denied. Admin privileges required.";
            return false;
        }
    }

    // remove a user
    bool removeUsers(const QString& studentName) {
        bool removed = false;
        if (hasAdminAccess()) {
            QFile fileOpen("/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/userlogininfo.txt");

            // open the file in read mode
            if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Error opening file for reading.";
                return false;
            }

            QStringList allLines;
            QTextStream input(&fileOpen);

            // read all lines except the one matching the student's name
            while (!input.atEnd()) {
                QString line = input.readLine();
                QStringList parts = line.split("/");

                // only add lines that don't match the student's name
                if (parts.size() > 0 && parts[0] != studentName) {
                    allLines.append(line);
                } else if (parts[0] == studentName) {
                    qDebug() << "Student Confirmed. Student Removed.";
                    removed = true;
                }
            }

            fileOpen.close();

            // open the file in write mode to overwrite it
            if (!fileOpen.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                qDebug() << "Error opening file for writing.";
                return false;
            }

            QTextStream output(&fileOpen);

            // write back the filtered lines
            for (const QString& line : allLines) {
                output << line << "\n";
            }

            fileOpen.close();
        } else {
            qDebug() << "Access Denied: Only administrators can remove users.\n";
        }
        return removed;
    }

    // check if the user has admin access
    bool hasAdminAccess() const {
        qDebug() << "Checking admin access for UserID:" << QString::fromStdString(admin->getUserID());

        if (admin->getUserID() == "admin1") {
            return true;
        } else {
            qDebug() << "Not Admin1" << QString::fromStdString(admin->getUserID());
            return false;
        }
    }

private:
    Admin* admin;
};

#endif // ADMINPROXY_H
