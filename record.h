#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <ctime>
#include "enums.h"

using namespace std;

// 流水记录类：封装单笔操作日志
// 记录购物卡的每一笔操作（充值、消费、退款、挂失、解锁）
// 包含操作类型、金额、时间、操作员等信息
class Record
{
private:
    string recordId;       // 记录ID
    string cardId;         // 关联的购物卡ID
    RecordType type;       // 操作类型
    double amount;         // 操作金额
    time_t operateTime;    // 操作时间
    string operatorName;   // 操作员名称

public:
    Record();                                               // 默认构造函数
    Record(string id, string cid, RecordType t, double amt, string opName); // 带参数构造函数

    string getRecordId() const;       // 获取记录ID
    string getCardId() const;         // 获取关联购物卡ID
    RecordType getType() const;       // 获取操作类型
    double getAmount() const;         // 获取操作金额
    time_t getOperateTime() const;    // 获取操作时间
    string getOperatorName() const;   // 获取操作员名称

    string toString() const;          // 将记录转换为字符串格式，用于文件存储和显示
};

#endif