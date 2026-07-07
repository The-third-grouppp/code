#include "record.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Record::Record() : m_recordId(0), m_cardId(""), m_type(RECHARGE),  m_amount(0.0), m_balance(0.0), m_operator(""), m_timestamp(0), m_remark("") {}

Record::Record(int id, const string& cardId, RecordType type, double amount, double balance, const string& operatorName,time_t time, const string& remark): m_recordId(id), m_cardId(cardId), m_type(type), m_amount(amount), m_balance(balance), m_operator(operatorName),m_timestamp(time), m_remark(remark) {}

int Record::getRecordId() const { return m_recordId; }
string Record::getCardId() const { return m_cardId; }
RecordType Record::getType() const { return m_type; }
double Record::getAmount() const { return m_amount; }
double Record::getBalance() const { return m_balance; }
string Record::getOperator() const { return m_operator; }
time_t Record::getTimestamp() const { return m_timestamp; }
string Record::getRemark() const { return m_remark; }

void Record::display() const {
    cout << "Record ID: " << m_recordId << ", Card: " << m_cardId << ", Amount: " << m_amount << ", Balance: " << m_balance << endl;
}

// 序列化：用 | 分隔字段
string Record::toString() const {
    stringstream ss;
    ss << m_recordId << "|"<< m_cardId << "|" << (int)m_type << "|"<< m_amount << "|"<< m_balance << "|"<< m_operator << "|"<< m_timestamp << "|"<< m_remark;
    return ss.str();
}

// 反序列化：从文本行解析
Record Record::fromString(const string& line) {
    stringstream ss(line);
    string token;
    int id, typeInt;
    string cardId, operatorName, remark;
    double amount, balance;
    time_t timestamp;

    getline(ss, token, '|'); 
    id = stoi(token);
    getline(ss, cardId, '|');
    getline(ss, token, '|'); 
    typeInt = stoi(token);
    getline(ss, token, '|'); 
    amount = stod(token);
    getline(ss, token, '|');
     balance = stod(token);
    getline(ss, operatorName, '|');
    getline(ss, token, '|'); 
    timestamp = stoll(token);
    getline(ss, remark, '|');
    return Record(id, cardId, (RecordType)typeInt, amount, balance, operatorName, timestamp, remark);
}