#include "filemanager.h"
#include <fstream>
#include <sstream>

FileManager::FileManager() 
    : userFilePath("users.txt"), 
      cardTemplateFilePath("templates.txt"), 
      shoppingCardFilePath("cards.txt"), 
      recordFilePath("records.txt") {}

FileManager::FileManager(const std::string& userFile, const std::string& tplFile, 
                         const std::string& cardFile, const std::string& recordFile)
    : userFilePath(userFile), cardTemplateFilePath(tplFile), 
      shoppingCardFilePath(cardFile), recordFilePath(recordFile) {}

bool FileManager::saveUsers(const std::vector<User>& users)
{
    std::ofstream file(userFilePath);
    if (!file) return false;
    for (const auto& user : users)
    {
        file << user.getUsername() << "|" << user.getPassword() << "|" << user.getRole() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadUsers(std::vector<User>& users)
{
    std::ifstream file(userFilePath);
    if (!file) return false;
    users.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string username, password;
        int role;
        std::getline(iss, username, '|');
        std::getline(iss, password, '|');
        iss >> role;
        users.emplace_back(username, password, static_cast<Role>(role));
    }
    file.close();
    return true;
}

bool FileManager::saveCardTemplates(const std::vector<CardTemplate>& templates)
{
    std::ofstream file(cardTemplateFilePath);
    if (!file) return false;
    for (const auto& tpl : templates)
    {
        file << tpl.getTemplateId() << "|" << tpl.getTemplateName() << "|" 
             << tpl.getMinAmount() << "|" << tpl.getMaxAmount() << "|" 
             << tpl.getDiscountRate() << "|" << tpl.getValidDays() << "|" 
             << tpl.getIsActive() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadCardTemplates(std::vector<CardTemplate>& templates)
{
    std::ifstream file(cardTemplateFilePath);
    if (!file) return false;
    templates.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string id, name;
        double minAmount, maxAmount, discountRate;
        int validDays;
        bool isActive;
        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        iss >> minAmount; iss.ignore(1);
        iss >> maxAmount; iss.ignore(1);
        iss >> discountRate; iss.ignore(1);
        iss >> validDays; iss.ignore(1);
        iss >> isActive;
        CardTemplate tpl(id, name, minAmount, maxAmount, discountRate, validDays);
        tpl.setIsActive(isActive);
        templates.push_back(tpl);
    }
    file.close();
    return true;
}

bool FileManager::saveShoppingCards(const std::vector<ShoppingCard>& cards)
{
    std::ofstream file(shoppingCardFilePath);
    if (!file) return false;
    for (const auto& card : cards)
    {
        file << card.getCardId() << "|" << card.getHolderName() << "|" 
             << card.getBalance() << "|" << card.getStatus() << "|" 
             << card.getPhone() << "|" << card.getTemplateId() << "|" 
             << card.getCreateTime() << "|" << card.getExpireTime() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadShoppingCards(std::vector<ShoppingCard>& cards)
{
    std::ifstream file(shoppingCardFilePath);
    if (!file) return false;
    cards.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string cardId, holderName, phone, templateId;
        double balance;
        int status;
        std::time_t createTime, expireTime;
        std::getline(iss, cardId, '|');
        std::getline(iss, holderName, '|');
        iss >> balance; iss.ignore(1);
        iss >> status; iss.ignore(1);
        std::getline(iss, phone, '|');
        std::getline(iss, templateId, '|');
        iss >> createTime; iss.ignore(1);
        iss >> expireTime;
        ShoppingCard card(cardId, holderName, templateId, balance, phone, expireTime);
        card.setStatus(static_cast<CardStatus>(status));
        cards.push_back(card);
    }
    file.close();
    return true;
}

bool FileManager::saveRecords(const std::vector<Record>& records)
{
    std::ofstream file(recordFilePath);
    if (!file) return false;
    for (const auto& record : records)
    {
        file << record.getRecordId() << "|" << record.getCardId() << "|" 
             << static_cast<int>(record.getType()) << "|" << record.getAmount() << "|" 
             << record.getBalanceAfter() << "|" << record.getOperateTime() << "|" 
             << record.getOperatorName() << "|" << record.getDescription() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadRecords(std::vector<Record>& records)
{
    std::ifstream file(recordFilePath);
    if (!file) return false;
    records.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string recordId, cardId, operatorName, description;
        int type;
        double amount, balanceAfter;
        std::time_t operateTime;
        std::getline(iss, recordId, '|');
        std::getline(iss, cardId, '|');
        iss >> type; iss.ignore(1);
        iss >> amount; iss.ignore(1);
        iss >> balanceAfter; iss.ignore(1);
        iss >> operateTime; iss.ignore(1);
        std::getline(iss, operatorName, '|');
        std::getline(iss, description);
        records.emplace_back(recordId, cardId, static_cast<RecordType>(type), 
                            amount, balanceAfter, operatorName, description);
    }
    file.close();
    return true;
}
