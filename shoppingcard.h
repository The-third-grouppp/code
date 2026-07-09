#ifndef SHOPPINGCARD_H
#define SHOPPINGCARD_H

#include <string>
#include <vector>
#include <ctime>
#include "enums.h"
#include "record.h"

using namespace std;

// 购物卡核心类：封装单张卡片的所有属性和行为
// 负责购物卡的充值、消费、退款、挂失、解锁等核心操作
// 维护卡片状态和流水记录
class ShoppingCard
{
private:
    string cardId;         // 卡号
    string holderName;     // 持卡人姓名
    double balance;        // 余额
    CardStatus status;     // 卡片状态
    string templateId;     // 关联的卡模板ID
    time_t createTime;     // 创建时间
    time_t expireTime;     // 过期时间
    vector<Record> records; // 流水记录列表

public:
    ShoppingCard();                                // 默认构造函数
    ShoppingCard(string id, string name, string tplId, time_t expire); // 带参数构造函数

    bool recharge(double amount);                  // 充值，返回是否成功
    bool consume(double amount);                   // 消费，返回是否成功
    bool refund(double amount);                    // 退款，返回是否成功
    bool reportLost();                             // 挂失，返回是否成功
    bool unlock();                                 // 解锁/解除挂失，返回是否成功
    bool cancelCard();                             // 注销卡片，返回是否成功

    string getCardId() const;         // 获取卡号
    string getHolderName() const;     // 获取持卡人姓名
    double getBalance() const;        // 获取余额
    CardStatus getStatus() const;     // 获取卡片状态
    string getTemplateId() const;     // 获取关联模板ID
    time_t getCreateTime() const;     // 获取创建时间
    time_t getExpireTime() const;     // 获取过期时间
    vector<Record> getRecords() const; // 获取流水记录列表

    void setHolderName(string name);         // 设置持卡人姓名
    void setStatus(CardStatus newStatus);    // 设置卡片状态
    void setExpireTime(time_t newExpire);    // 设置过期时间

    bool isValid() const;           // 检查卡片是否有效（未过期、未注销）
    bool canOperate() const;        // 检查卡片是否可操作（有效且未挂失/锁定）
};

#endif