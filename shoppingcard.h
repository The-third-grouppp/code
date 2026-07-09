#ifndef SHOPPINGCARD_H
#define SHOPPINGCARD_H

#include <string>
#include <vector>
#include <ctime>
#include "enums.h"
#include "record.h"

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

    std::string getCardId() const;
    std::string getHolderName() const;
    double getBalance() const;
    CardStatus getStatus() const;
    std::string getPhone() const;
    std::string getTemplateId() const;
    std::time_t getCreateTime() const;
    std::time_t getExpireTime() const;
    const std::vector<Record>& getRecords() const;

    void setHolderName(const std::string& name);
    void setPhone(const std::string& phone);
    void setStatus(CardStatus newStatus);
    void setExpireTime(std::time_t newExpire);

    bool isValid() const;
    bool canOperate() const;
};

#endif
