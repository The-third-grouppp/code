#ifndef RECORD_H
#define RECORD_H
#include "enums.h"  
#include <string>
#include <ctime>
using namespace std;

class Record{
    private:
    int m_recordId;//流水的编号
    string m_cardId;//关联的卡号
    RecordType m_type;//shoppingcard.h的枚举类
    double m_amount;//金额
    double m_balance;//余额
    string m_operator;//操作人
    time_t m_timestamp;//操作时间
    string m_remark;//备注:干了什么

public:
    Record();
    Record(int id, const string& cardId, RecordType type, double amount, double balance, const string& operatorName,time_t time, const string& remark = "");
    //全只读
    int getRecordId() const;
    string getCardId() const;
    RecordType getType() const;
    double getAmount() const;
    double getBalance() const;
    string getOperator() const;
    time_t getTimestamp() const;
    string getRemark() const;

    void display() const;
    
    string toString() const; // 序列化：将对象转成一行文本（用于写入文件）
    static Record fromString(const string& line);// 反序列化：从一行文本解析出Record对象
};
#endif