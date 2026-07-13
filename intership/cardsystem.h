#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <vector>
#include <memory>
#include "user.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include "record.h"
#include "filemanager.h"

class CardSystem
{
private:
    std::vector<User> users;
    std::vector<CardTemplate> cardTemplates;
    std::vector<ShoppingCard> shoppingCards;
    std::vector<Record> records;
    FileManager fileManager;
    std::string currentUsername;
    
    std::string getRoleName(Role role) const;
    std::string getStatusName(CardStatus status) const;
    std::string getRecordTypeName(RecordType type) const;
    std::string formatTime(std::time_t timestamp) const;
    void displayMenu();

    void handleLoginChoice(int choice);
    void handleMenuChoice(int choice);

    void handleRecharge();
    void handleConsume();
    void handleRefund();
    void handleReportLost();
    void handleUnlock();
    void handleFreeze();
    void handleUnfreeze();
    void handleQueryBalance();
    void handleCreateCard();
    void handleViewAllCards();
    void handleQueryRecords();

    void handleAddTemplate();
    void handleModifyTemplate();
    void handleDeleteTemplate();
    void handleViewAllTemplates();

    void handleAddUser();
    void handleModifyUser();
    void handleDeleteUser();
    void handleViewAllUsers();

    void handleTransfer();
    void handleSaveData();
    void handleLogout();

    std::string generateCardId();
    ShoppingCard* findShoppingCard(const std::string& cardId);

public:
    CardSystem();
    ~CardSystem();

    bool initSystem();
    bool login(const std::string& username, const std::string& password);
    void logout();
    User* getCurrentUser();

    bool addUser(const User& user);
    bool removeUser(const std::string& username);
    bool modifyUser(const User& user);
    std::vector<User> getAllUsers();

    bool addCardTemplate(const CardTemplate& tpl);
    bool removeCardTemplate(const std::string& tplId);
    bool modifyCardTemplate(const CardTemplate& tpl);
    std::vector<CardTemplate> getAllCardTemplates();

    bool createShoppingCard(const std::string& holderName, const std::string& phone, const std::string& templateId);
    bool deleteShoppingCard(const std::string& cardId);
    bool modifyShoppingCard(const ShoppingCard& card);
    std::vector<ShoppingCard> getAllShoppingCards();

    bool addRecord(const Record& record);
    std::vector<Record> getRecordsByCardId(const std::string& cardId);
    std::vector<Record> getAllRecords();

    bool saveAllData();
    bool loadAllData();

    void runMainLoop();

};

#endif
