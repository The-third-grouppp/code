#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <vector>
#include "user.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include "record.h"
#include "filemanager.h"

using namespace std;

// 系统总调度类：管理容器、菜单、权限、全局业务逻辑
// 作为系统的门面(Facade)，整合所有功能模块
// 提供统一的系统入口和业务调度
class CardSystem
{
private:
    vector<User> users;                    // 用户容器
    vector<CardTemplate> cardTemplates;    // 卡模板容器
    vector<ShoppingCard> shoppingCards;    // 购物卡容器
    vector<Record> records;                // 流水记录容器
    FileManager fileManager;               // 文件管理器
    User* currentUser;                     // 当前登录用户

public:
    CardSystem();                          // 构造函数，初始化系统
    ~CardSystem();                         // 析构函数

    bool initSystem();                     // 系统初始化（加载数据、创建默认管理员等）
    bool login(string username, string password); // 用户登录
    void logout();                         // 用户登出
    User* getCurrentUser();                // 获取当前登录用户

    bool addUser(const User& user);        // 添加用户
    bool removeUser(const string& username); // 删除用户
    bool modifyUser(const User& user);     // 修改用户信息
    vector<User> getAllUsers();            // 获取所有用户列表

    bool addCardTemplate(const CardTemplate& tpl); // 添加卡模板
    bool removeCardTemplate(const string& tplId);  // 删除卡模板
    bool modifyCardTemplate(const CardTemplate& tpl); // 修改卡模板
    vector<CardTemplate> getAllCardTemplates();   // 获取所有卡模板列表

    bool createShoppingCard(const string& holderName, const string& templateId); // 创建购物卡
    bool deleteShoppingCard(const string& cardId); // 删除购物卡
    bool modifyShoppingCard(const ShoppingCard& card); // 修改购物卡信息
    ShoppingCard* findShoppingCard(const string& cardId); // 根据卡号查找购物卡
    vector<ShoppingCard> getAllShoppingCards(); // 获取所有购物卡列表

    bool addRecord(const Record& record);  // 添加流水记录
    vector<Record> getRecordsByCardId(const string& cardId); // 根据卡号获取流水记录
    vector<Record> getAllRecords();       // 获取所有流水记录

    bool saveAllData();                    // 保存所有数据到文件
    bool loadAllData();                    // 从文件加载所有数据

    void runMainLoop();                    // 控制台主循环，显示菜单并处理用户输入
};

#endif