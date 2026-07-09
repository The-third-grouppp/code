#ifndef ENUMS_H
#define ENUMS_H

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
    UNLOCK_OP,
    TRANSFER_OUT,
    TRANSFER_IN
};

#endif
