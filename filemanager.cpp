#include "filemanager.h"
#include <fstream>
#include <iostream>
using namespace std;

const string FileManager::RECORD_FILE = "records.txt";

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