#ifndef USER_H
#define USER_H

#include <string>
#include "enums.h"

using namespace std;

// 用户类：封装账号、角色、登录校验功能
// 负责用户信息的管理，包括登录、登出、权限验证等操作
class User
{
private:
    string username;     // 用户名
    string password;     // 密码
    Role role;           // 用户角色
    bool isOnline;       // 是否在线

public:
    User();                              // 默认构造函数
    User(string name, string pwd, Role r); // 带参数构造函数

    bool login(string inputPwd);         // 登录验证，返回是否成功
    void logout();                       // 登出
    bool validate(Role requiredRole);    // 权限验证，检查是否具有指定角色权限

    string getUsername() const;          // 获取用户名
    Role getRole() const;                // 获取用户角色
    bool getIsOnline() const;            // 获取在线状态
    void setPassword(string newPwd);     // 修改密码
};

#endif