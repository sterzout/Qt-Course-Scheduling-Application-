#ifndef USER_H
#define USER_H

#include <string>


class User {
public:
    //variables which go into the constructor
    std::string name;
    std::string userID;
    std::string email;
    std::string password;

    // constructor
    User(const std::string& name, const std::string& userID, const std::string& email, const std::string& password);
    virtual ~User() {} // Ensure proper cleanup in derived classes

    // getters
     std::string getName() const;
     std::string getUserID() const;
     std::string getEmail() const;
     std::string getPassword() const;



    // static factory method to create User objects based on userID
    static User* createUser(const std::string& name, const std::string& userID, const std::string& email, const std::string& password);
};

#endif
