#include "shoppingcard.h"
#include <sstream>

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
    records.push_back(Record(RECORD_RECHARGE, amount, "��Ƭ��ֵ", time(nullptr)));
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
    records.push_back(Record(RECORD_CONSUME, amount, "��Ƭ����", time(nullptr)));
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
    records.push_back(Record(RECORD_REFUND, amount, "�����˿�", time(nullptr)));
    return true;
}

bool ShoppingCard::reportLost()
{
    if (!isValid() || status != NORMAL)
    {
        return false;
    }

    status = LOST;
    records.push_back(Record(RECORD_LOST, 0.0, "��Ƭ��ʧ", time(nullptr)));
    return true;
}

bool ShoppingCard::unlock()
{
    if (!isValid() || status != LOST)
    {
        return false;
    }

    status = NORMAL;
    records.push_back(Record(RECORD_UNLOCK, 0.0, "�����ʧ", time(nullptr)));
    return true;
}

bool ShoppingCard::cancelCard()
{
    if (status == CANCELLED)
    {
        return false;
    }

    status = CANCELLED;
    records.push_back(Record(RECORD_CANCEL, 0.0, "��Ƭע��", time(nullptr)));
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

string ShoppingCard::toString() const {
    stringstream ss;
    ss << cardId << "|" << holderName << "|" << balance << "|" << (int)status << "|"
       << templateId << "|" << createTime << "|" << expireTime;
    return ss.str();
}

ShoppingCard ShoppingCard::fromString(const string& line) {
    stringstream ss(line);
    string cardId, holderName, templateId, token;
    double balance;
    int statusInt;
    time_t create, expire;
    getline(ss, cardId, '|');
    getline(ss, holderName, '|');
    getline(ss, token, '|'); balance = stod(token);
    getline(ss, token, '|'); statusInt = stoi(token);
    getline(ss, templateId, '|');
    getline(ss, token, '|'); create = stoll(token);
    getline(ss, token, '|'); expire = stoll(token);
    ShoppingCard card(cardId, holderName, templateId, expire);
    card.setBalance(balance);
    card.setStatus((CardStatus)statusInt);
    return card;
}