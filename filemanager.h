#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "user.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include "record.h"

using namespace std;

// 文件持久化类：统一读写txt文件的工具类
// 负责所有数据的持久化存储，包括用户、卡模板、购物卡、流水记录
// 提供统一的save/load接口，所有类数据存取都通过此类进行
class FileManager
{
private:
    string userFilePath;            // 用户数据文件路径
    string cardTemplateFilePath;    // 卡模板数据文件路径
    string shoppingCardFilePath;    // 购物卡数据文件路径
    string recordFilePath;          // 流水记录文件路径

public:
    FileManager();                                               // 默认构造函数，使用默认文件路径
    FileManager(string userFile, string tplFile, string cardFile, string recordFile); // 带参数构造函数

    bool saveUsers(const vector<User>& users);                   // 保存用户数据到文件
    bool loadUsers(vector<User>& users);                         // 从文件加载用户数据

    bool saveCardTemplates(const vector<CardTemplate>& templates); // 保存卡模板数据到文件
    bool loadCardTemplates(vector<CardTemplate>& templates);     // 从文件加载卡模板数据

    bool saveShoppingCards(const vector<ShoppingCard>& cards);   // 保存购物卡数据到文件
    bool loadShoppingCards(vector<ShoppingCard>& cards);         // 从文件加载购物卡数据

    bool saveRecords(const vector<Record>& records);             // 保存流水记录到文件
    bool loadRecords(vector<Record>& records);                   // 从文件加载流水记录

    string generateId(const string& prefix);                     // 生成唯一ID，prefix为前缀（如：USR、CRD、RCD）
};

#endif