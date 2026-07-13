#ifndef SHOPPINGCARD_H
#define SHOPPINGCARD_H
#include <string>
#include <vector>
#include <ctime>
#include "enums.h"
#include "record.h"
#include "cardtemplate.h" // 新增：依赖卡模板类

class ShoppingCard
{
private:
    std::string cardId;
    std::string holderName;
    double balance;
    CardStatus status;
    std::string phone;
    std::string templateId;
    std::time_t createTime;
    std::time_t expireTime;
    std::vector<Record> records;
    double totalRecharge;

    std::string generateTransactionId();
    bool addTransaction(RecordType type, double amount, const std::string& description);
public:
    ShoppingCard();
    ShoppingCard(const std::string& id, const std::string& name, const std::string& tplId, 
                 double initialBalance, const std::string& phone, std::time_t expire);
    
    bool recharge(double amount, const std::string& description);
    bool consume(double amount, const std::string& description);
    bool refund(double amount, const std::string& description);
    bool reportLost();
    bool unlock();
    bool freeze();
    bool unfreeze();
    bool cancelCard();
    bool upgrade(const std::string& newTemplateId, const std::string& description = "");

    // ========== 新增：卡片业务内聚函数 ==========
    // 根据全局模板列表，返回当前卡片的折扣率
    double getDiscount(const std::vector<CardTemplate>& templates) const;
    // 统一退款规则：输入账面退款额，返回实际返还现金（固定0.8）
    double getActualRefundCash(double refundAmount) const;
    // 根据累计充值自动判断升级目标模板，无需升级返回空串
    std::string getAutoUpgradeTemplateId(double totalRechargeVal);

    std::string getCardId() const;
    std::string getHolderName() const;
    double getBalance() const;
    CardStatus getStatus() const;
    std::string getPhone() const;
    std::string getTemplateId() const;
    std::time_t getCreateTime() const;
    std::time_t getExpireTime() const;
    const std::vector<Record>& getRecords() const;
    double getTotalRecharge() const;

    void setHolderName(const std::string& name);
    void setPhone(const std::string& ph);
    void setStatus(CardStatus newStatus);
    void setExpireTime(std::time_t newExpire);
    void setTemplateId(const std::string& tplId);
    void setTotalRecharge(double total);

    bool isValid() const;
    bool canOperate() const;
};
#endif
