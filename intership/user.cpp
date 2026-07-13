#include "user.h"

User::User() : username(""), password(""), role(SUPER_ADMIN), isOnline(false) {}

User::User(const std::string& name, const std::string& pwd, Role r)
    : username(name), password(pwd), role(r), isOnline(false) {}

bool User::login(const std::string& inputPwd)
{
    if (password == inputPwd)
    {
        isOnline = true;
        return true;
    }
    return false;
}

void User::logout()
{
    isOnline = false;
}

bool User::validate(Role requiredRole)
{
    if (!isOnline)
        return false;

    if (role == SUPER_ADMIN)
        return true;

    if (role == CARD_ADMIN && requiredRole == CARD_ADMIN)
        return true;

    if (role == CASHIER && requiredRole == CASHIER)
        return true;

    if (role == FINANCE && requiredRole == FINANCE)
        return true;

    return false;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

Role User::getRole() const
{
    return role;
}

bool User::getIsOnline() const
{
    return isOnline;
}

void User::setPassword(const std::string& newPwd)
{
    password = newPwd;
}

