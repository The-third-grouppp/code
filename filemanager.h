#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "record.h"
#include <vector>
#include <string>
using namespace std;

class FileManager {
public:
    static const string RECORD_FILE;
    static bool saveRecords(const vector<Record>& records);
    static vector<Record> loadRecords();
};
#endif