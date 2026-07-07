#ifndef USER_H
#define USER_H

#include <string>
#include "enums.h"

using namespace std;
class User
{
private:
    string username;
    string password;
    Role role;
    string realName;
public:
    User(string u, string p, Role r, string n);

    string getUsername() const;
    Role getRole() const;
    string getName() const;

    bool changePwd(string oldPwd, string newPwd);
    bool checkPwd(string pwd) const;
    bool isSuperAdmin() const;
    void showInfo() const;
    string toFileStr() const;
};
#endif
