#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <ctime>
#include "enums.h"

class Record
{
private:
    std::string recordId;
    std::string cardId;
    RecordType type;
    double amount;
    double balanceAfter;
    std::time_t operateTime;
    std::string operatorName;
    std::string description;

public:
    Record();
    Record(const std::string& id, const std::string& cid, RecordType t, double amt, double balAfter, const std::string& opName, const std::string& desc = "");

    std::string getRecordId() const;
    std::string getCardId() const;
    RecordType getType() const;
    double getAmount() const;
    double getBalanceAfter() const;
    std::time_t getOperateTime() const;
    std::string getOperatorName() const;
    std::string getDescription() const;
};

#endif
