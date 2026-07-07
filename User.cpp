#include"User.h" 
User::User(string u, string p, Role r, string n)
    : username(u), password(p), role(r), realName(n) {}

string User::getUsername() const { return username; }
Role User::getRole() const { return role; }
string User::getName() const { return realName; }

bool User::changePwd(string oldPwd, string newPwd)
{
    if (password == oldPwd)
    {
        password = newPwd;
        return true;
    }
    return false;
}

bool User::checkPwd(string pwd) const
{
    return password == pwd;
}

bool User::isSuperAdmin() const
{
    return role == SUPER_ADMIN;
}

void User::showInfo() const
{
    cout << "ÕËºÅ£º" << username << " ÐÕÃû£º" << realName << endl;
}

string User::toFileStr() const
{
    return username + "|" + password + "|" + to_string(role) + "|" + realName;
}
