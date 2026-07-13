#include "record.h"
#include <sstream>
#include <iomanip>

Record::Record() 
    : recordId(""), cardId(""), type(RECHARGE), amount(0), balanceAfter(0), 
      operateTime(std::time(nullptr)), operatorName(""), description("") {}

Record::Record(const std::string& id, const std::string& cid, RecordType t, double amt, double balAfter, const std::string& opName, const std::string& desc)
    : recordId(id), cardId(cid), type(t), amount(amt), balanceAfter(balAfter), 
      operateTime(std::time(nullptr)), operatorName(opName), description(desc) {}

std::string Record::getRecordId() const { return recordId; }
std::string Record::getCardId() const { return cardId; }
RecordType Record::getType() const { return type; }
double Record::getAmount() const { return amount; }
double Record::getBalanceAfter() const { return balanceAfter; }
std::time_t Record::getOperateTime() const { return operateTime; }
std::string Record::getOperatorName() const { return operatorName; }
std::string Record::getDescription() const { return description; }

std::string Record::toString() const
{
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&operateTime));

    std::ostringstream oss;
    oss << recordId << "|" << cardId << "|" << static_cast<int>(type) 
        << "|" << amount << "|" << balanceAfter << "|" << timeStr 
        << "|" << operatorName << "|" << description;
    return oss.str();
}