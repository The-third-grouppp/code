#include <iostream>
#include <string>
#include "QueryService.h" 

using namespace std;

int main() {
    string filePath = "records.txt"; 
    string myCardId;

    cout << "请输入需要查询余额的卡号：";
    cin >> myCardId;
    
    double currentBalance = queryBalance(filePath, myCardId);

    cout << "===========================" << endl;
    cout << "卡号: " << myCardId << endl;
    cout << "最新余额: " << currentBalance << " 元" << endl;
    cout << "===========================" << endl;

    return 0;
}