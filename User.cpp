#include"User.h" 
#include<sstream>
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
    cout << "�˺ţ�" << username << " ������" << realName << endl;
}

string User::toString() const {
    stringstream ss;
    ss << username << "|" << password << "|" << (int)role << "|" << realName;
    return ss.str();
}

User User::fromString(const string& line) {
    stringstream ss(line);
    string username, password, realName, token;
    int roleInt;
    getline(ss, username, '|');
    getline(ss, password, '|');
    getline(ss, token, '|');
    roleInt = stoi(token);
    getline(ss, realName, '|');
    return User(username, password, (Role)roleInt, realName);
}