#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "user.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include "record.h"

class FileManager
{
private:
    std::string userFilePath;
    std::string cardTemplateFilePath;
    std::string shoppingCardFilePath;
    std::string recordFilePath;

public:
    FileManager();
    FileManager(const std::string& userFile, const std::string& tplFile, 
                const std::string& cardFile, const std::string& recordFile);

    bool saveUsers(const std::vector<User>& users);
    bool loadUsers(std::vector<User>& users);

    bool saveCardTemplates(const std::vector<CardTemplate>& templates);
    bool loadCardTemplates(std::vector<CardTemplate>& templates);

    bool saveShoppingCards(const std::vector<ShoppingCard>& cards);
    bool loadShoppingCards(std::vector<ShoppingCard>& cards);

    bool saveRecords(const std::vector<Record>& records);
    bool loadRecords(std::vector<Record>& records);

    std::string generateId(const std::string& prefix);
};

#endif
