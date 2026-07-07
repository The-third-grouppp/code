#include "filemanager.h"
#include <fstream>
#include <iostream>
using namespace std;

const string FileManager::RECORD_FILE = "records.txt";
const string FileManager::USER_FILE = "users.txt";
const string FileManager::TEMPLATE_FILE = "templates.txt";
const string FileManager::CARD_FILE = "cards.txt";

bool FileManager::saveRecords(const vector<Record>& records) {
    ofstream outFile(RECORD_FILE);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open file " << RECORD_FILE << " for writing." << endl;
        return false;
    }
    for (const auto& rec : records) {
        outFile << rec.toString() << endl;
    }
    outFile.close();
    return true;
}

vector<Record> FileManager::loadRecords() {
    vector<Record> records;
    ifstream inFile(RECORD_FILE);
    if (!inFile.is_open()) {
        return records;
    }
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Record rec = Record::fromString(line);
            records.push_back(rec);
        }
    }
    inFile.close();
    return records;
}

bool FileManager::saveUsers(const vector<User>& users) {
    ofstream outFile(USER_FILE);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open " << USER_FILE << " for writing." << endl;
        return false;
    }
    for (const auto& u : users) {
        outFile << u.toString() << endl;
    }
    outFile.close();
    return true;
}

vector<User> FileManager::loadUsers() {
    vector<User> users;
    ifstream inFile(USER_FILE);
    if (!inFile.is_open()) {
        return users;  
    }
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            users.push_back(User::fromString(line));
        }
    }
    return users;
}

bool FileManager::saveTemplates(const vector<CardTemplate>& templates) {
    ofstream outFile(TEMPLATE_FILE);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open " << TEMPLATE_FILE << " for writing." << endl;
        return false;
    }
    for (const auto& t : templates) {
        outFile << t.toString() << endl;
    }
    outFile.close();
    return true;
}

vector<CardTemplate> FileManager::loadTemplates() {
    vector<CardTemplate> templates;
    ifstream inFile(TEMPLATE_FILE);
    if (!inFile.is_open()) {
        return templates;
    }
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            templates.push_back(CardTemplate::fromString(line));
        }
    }
    return templates;
}

bool FileManager::saveCards(const vector<ShoppingCard>& cards) {
    ofstream outFile(CARD_FILE);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open " << CARD_FILE << " for writing." << endl;
        return false;
    }
    for (const auto& c : cards) {
        outFile << c.toString() << endl;
    }
    outFile.close();
    return true;
}

vector<ShoppingCard> FileManager::loadCards() {
    vector<ShoppingCard> cards;
    ifstream inFile(CARD_FILE);
    if (!inFile.is_open()) {
        return cards;
    }
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            cards.push_back(ShoppingCard::fromString(line));
        }
    }
    return cards;
}