#include "QueryService.h" 
#include "Record.h"       
#include <iostream>
#include <fstream>

using namespace std;

// 具体实现查询功能
double queryBalance(string filePath, string targetCardId) {
    ifstream inFile(filePath.c_str());
    if (inFile.is_open() == false) {
        cout << "错误：找不到流水记录文件！" << endl;
        return 0.0;
    }
    
    string line;
    double finalBalance = 0.0; 

    while (getline(inFile, line)) {
        if (line == "") {
            continue; 
        }

        Record r = Record::fromString(line);

        if (r.getCardId() == targetCardId) {
            finalBalance = r.getBalance();
        }
    }

    inFile.close(); 
    return finalBalance;
}