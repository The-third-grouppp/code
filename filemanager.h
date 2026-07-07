#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "record.h"
#include "User.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include <vector>
#include <string>
using namespace std;

class FileManager {
public:
    static const string RECORD_FILE;
    static bool saveRecords(const vector<Record>& records);
    static vector<Record> loadRecords();
    static const string USER_FILE;
    static const string TEMPLATE_FILE;
    static const string CARD_FILE;
    static bool saveUsers(const vector<User>& users);
    static vector<User> loadUsers();
    static bool saveTemplates(const vector<CardTemplate>& templates);
    static vector<CardTemplate> loadTemplates();
    static bool saveCards(const vector<ShoppingCard>& cards);
    static vector<ShoppingCard> loadCards();
};
#endif