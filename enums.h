#ifndef ENUMS_H
#define ENUMS_H

// 用户角色枚举
// SUPER_ADMIN: 超级管理员，拥有所有权限
// CARD_ADMIN: 卡管理员，负责卡模板管理
// CASHIER: 收银员，负责消费、充值等日常操作
// FINANCE: 财务人员，负责流水查询和统计
enum Role
{
    SUPER_ADMIN,
    CARD_ADMIN,
    CASHIER,
    FINANCE
};

// 购物卡状态枚举
// NORMAL: 正常状态，可正常使用
// ACTIVE: 激活状态
// LOCK: 锁定状态，暂时无法使用
// LOST: 挂失状态，已挂失
// EXPIRE: 过期状态，已过期
// CANCEL: 注销状态，已注销
enum CardStatus
{
    NORMAL,
    ACTIVE,
    LOCK,
    LOST,
    EXPIRE,
    CANCEL
};

// 流水记录类型枚举
// RECHARGE: 充值记录
// CONSUME: 消费记录
// REFUND: 退款记录
// LOST_OP: 挂失操作记录
// UNLOCK_OP: 解锁/解除挂失记录
enum RecordType
{
    RECHARGE,
    CONSUME,
    REFUND,
    LOST_OP,
    UNLOCK_OP
};

#endif