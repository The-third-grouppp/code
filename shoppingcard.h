#ifndef SHOPPINGCARD_H
#define SHOPPINGCARD_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;


enum Role
{
    SUPER_ADMIN,
    CARD_ADMIN,
    CASHIER,
    FINANCE
};

enum CardStatus
{
    NORMAL,   
    ACTIVE,   
    LOCK,      
    LOST,      
    EXPIRE,    
    CANCEL    
};

enum RecordType
{
    RECHARGE,
    CONSUME,
    REFUND,
    LOST_OP,
    UNLOCK_OP
};



#endif
