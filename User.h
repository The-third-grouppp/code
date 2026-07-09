#ifndef USER_H
#define USER_H

#include <string>
#include "enums.h"

class User
{
private:
    std::string username;
    std::string password;
    Role role;
    bool isOnline;

public:
    User();
    User(const std::string& name, const std::string& pwd, Role r);

    bool login(const std::string& inputPwd);
    void logout();
    bool validate(Role requiredRole);

    std::string getUsername() const;
    std::string getPassword() const;
    Role getRole() const;
    bool getIsOnline() const;
    void setPassword(const std::string& newPwd);
};

#endif
