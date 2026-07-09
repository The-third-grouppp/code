#include "shoppingcard.h"
#include <random>
#include <sstream>
#include <iomanip>

ShoppingCard::ShoppingCard()
    : cardId(""), holderName(""), balance(0.0), status(NORMAL),
      phone(""), templateId(""), createTime(std::time(nullptr)), expireTime(0) {}

ShoppingCard::ShoppingCard(const std::string& id, const std::string& name, const std::string& tplId,
                           double initialBalance, const std::string& ph, std::time_t expire)
    : cardId(id), holderName(name), balance(initialBalance), status(NORMAL),
      phone(ph), templateId(tplId), createTime(std::time(nullptr)), expireTime(expire)
{
    if (initialBalance > 0)
    {
        addTransaction(RECHARGE, initialBalance, "开卡充值");
    }
}

std::string ShoppingCard::generateTransactionId()
{
    static int counter = 0;
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << local->tm_year + 1900
        << std::setw(2) << std::setfill('0') << local->tm_mon + 1
        << std::setw(2) << std::setfill('0') << local->tm_mday
        << std::setw(6) << std::setfill('0') << ++counter;
    return oss.str();
}

bool ShoppingCard::addTransaction(RecordType type, double amount, const std::string& description)
{
    Record record(generateTransactionId(), cardId, type, amount, balance, "", description);
    records.push_back(record);
    return true;
}

bool ShoppingCard::recharge(double amount, const std::string& description)
{
    if (!canOperate()) return false;
    if (amount <= 0) return false;

    balance += amount;
    return addTransaction(RECHARGE, amount, description.empty() ? "充值" : description);
}

bool ShoppingCard::consume(double amount, const std::string& description)
{
    if (!canOperate()) return false;
    if (amount <= 0) return false;
    if (balance < amount) return false;

    balance -= amount;
    return addTransaction(CONSUME, amount, description.empty() ? "消费" : description);
}

bool ShoppingCard::refund(double amount, const std::string& description)
{
    if (!canOperate()) return false;
    if (amount <= 0) return false;

    balance += amount;
    return addTransaction(REFUND, amount, description.empty() ? "退款" : description);
}

bool ShoppingCard::reportLost()
{
    if (status == CANCEL || status == EXPIRE) return false;
    status = LOST;
    addTransaction(LOST_OP, 0, "挂失");
    return true;
}

bool ShoppingCard::unlock()
{
    if (status == CANCEL || status == EXPIRE) return false;
    status = NORMAL;
    addTransaction(UNLOCK_OP, 0, "解除挂失");
    return true;
}

bool ShoppingCard::freeze()
{
    if (status == LOST || status == EXPIRE || status == CANCEL) return false;
    status = LOCK;
    return true;
}

bool ShoppingCard::unfreeze()
{
    if (status != LOCK) return false;
    status = NORMAL;
    return true;
}

bool ShoppingCard::cancelCard()
{
    status = CANCEL;
    return true;
}

std::string ShoppingCard::getCardId() const { return cardId; }
std::string ShoppingCard::getHolderName() const { return holderName; }
double ShoppingCard::getBalance() const { return balance; }
CardStatus ShoppingCard::getStatus() const { return status; }
std::string ShoppingCard::getPhone() const { return phone; }
std::string ShoppingCard::getTemplateId() const { return templateId; }
std::time_t ShoppingCard::getCreateTime() const { return createTime; }
std::time_t ShoppingCard::getExpireTime() const { return expireTime; }
const std::vector<Record>& ShoppingCard::getRecords() const { return records; }

void ShoppingCard::setHolderName(const std::string& name) { holderName = name; }
void ShoppingCard::setPhone(const std::string& ph) { phone = ph; }
void ShoppingCard::setStatus(CardStatus newStatus) { status = newStatus; }
void ShoppingCard::setExpireTime(std::time_t newExpire) { expireTime = newExpire; }

bool ShoppingCard::isValid() const
{
    if (status == EXPIRE || status == CANCEL) return false;
    if (expireTime > 0 && std::time(nullptr) > expireTime) return false;
    return true;
}

bool ShoppingCard::canOperate() const
{
    if (!isValid()) return false;
    if (status == LOST || status == LOCK) return false;
    return true;
}
