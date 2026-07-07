#include "shoppingcard.h"

ShoppingCard::ShoppingCard()
    : cardId("")
    , holderName("")
    , balance(0.0)
    , status(NORMAL)
    , templateId("")
    , createTime(time(nullptr))
    , expireTime(0)
{
}

ShoppingCard::ShoppingCard(string id, string name, string tplId, time_t expire)
    : cardId(id)
    , holderName(name)
    , balance(0.0)
    , status(NORMAL)
    , templateId(tplId)
    , createTime(time(nullptr))
    , expireTime(expire)
{
}

bool ShoppingCard::recharge(double amount)
{
   
    if (amount <= 0)
    {
        return false;
    }
    if (!canOperate())
    {
        return false;
    }

    balance += amount;
    records.push_back(Record(RECORD_RECHARGE, amount, "¿¨Æ¬³äÖµ", time(nullptr)));
    return true;
}
bool ShoppingCard::consume(double amount)
{
    if (amount <= 0)
    {
        return false;
    }
    if (!canOperate())
    {
        return false;
    }
    if (balance < amount)
    {
        return false;
    }

    balance -= amount;
    records.push_back(Record(RECORD_CONSUME, amount, "¿¨Æ¬Ïû·Ñ", time(nullptr)));
    return true;
}

bool ShoppingCard::refund(double amount)
{
    if (amount <= 0)
    {
        return false;
    }
    if (!canOperate())
    {
        return false;
    }

    balance += amount;
    records.push_back(Record(RECORD_REFUND, amount, "Ïû·ÑÍË¿î", time(nullptr)));
    return true;
}

bool ShoppingCard::reportLost()
{
    if (!isValid() || status != NORMAL)
    {
        return false;
    }

    status = LOST;
    records.push_back(Record(RECORD_LOST, 0.0, "¿¨Æ¬¹ÒÊ§", time(nullptr)));
    return true;
}

bool ShoppingCard::unlock()
{
    if (!isValid() || status != LOST)
    {
        return false;
    }

    status = NORMAL;
    records.push_back(Record(RECORD_UNLOCK, 0.0, "½â³ý¹ÒÊ§", time(nullptr)));
    return true;
}

bool ShoppingCard::cancelCard()
{
    if (status == CANCELLED)
    {
        return false;
    }

    status = CANCELLED;
    records.push_back(Record(RECORD_CANCEL, 0.0, "¿¨Æ¬×¢Ïú", time(nullptr)));
    return true;
}

string ShoppingCard::getCardId() const
{
    return cardId;
}

string ShoppingCard::getHolderName() const
{
    return holderName;
}

double ShoppingCard::getBalance() const
{
    return balance;
}

CardStatus ShoppingCard::getStatus() const
{
    return status;
}

string ShoppingCard::getTemplateId() const
{
    return templateId;
}

time_t ShoppingCard::getCreateTime() const
{
    return createTime;
}

time_t ShoppingCard::getExpireTime() const
{
    return expireTime;
}

vector<Record> ShoppingCard::getRecords() const
{
    return records;
}

void ShoppingCard::setHolderName(string name)
{
    holderName = name;
}

void ShoppingCard::setStatus(CardStatus newStatus)
{
    status = newStatus;
}

void ShoppingCard::setExpireTime(time_t newExpire)
{
    expireTime = newExpire;
}

bool ShoppingCard::isValid() const
{   
    if (status == CANCELLED)
    {
        return false;
    }
    if (expireTime == 0)
    {
        return true;
    }
    time_t now = time(nullptr);
    return now < expireTime;
}

bool ShoppingCard::canOperate() const
{
    return isValid() && status == NORMAL;
}
