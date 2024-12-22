#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "course.h"
#include <iostream>
#include <QDebug>

class Admin : public User {
public:
    // constructor reuses user attributes
    Admin(const std::string& name, const std::string& userID, const std::string& email, const std::string& password)
        : User(name, userID, email, password) {}

    // will add course to selection
    void addCourse(Course* course) {
        qDebug() << "Admin: Adding course " << course->getCourseName() << "\n";
    }
    // will remove course from selection
    void removeCourse(Course* course) {
        qDebug() << "Admin: removed course " << course->getCourseName() << "\n";
    }
    // will remove user from list of users
    void removeUsers(QString& userName) {
        qDebug() <<  "Admin: Removing user " << userName << "\n";
    }
};

#endif // ADMIN_H
