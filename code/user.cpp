#include "user.h"
#include "student.h"
#include "admin.h"

//constructor
User::User(const std::string& name, const std::string& userID, const std::string& email, const std::string& password)
    : name(name), userID(userID), email(email), password(password) {}

// strings for all user attributes with their getters below
std::string User::getName() const {
    return name;
}

std::string User::getUserID() const {
    return userID;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}


User* User::createUser(const std::string& name, const std::string& userID, const std::string& email, const std::string& password) {
    // create and return user admin if admin1 userid
    if (userID == "admin1") {
        return new Admin(name, userID, email, password);
    } else {
        // else return new Student object
        return new Student(name, userID, email, password);
    }
}
