#include "cardsystem.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <iomanip>
CardSystem::CardSystem()
{
    initSystem();
}

CardSystem::~CardSystem()
{
    saveAllData();
}

bool CardSystem::initSystem()
{
    loadAllData();//jiazaihanshu
    if (users.empty())
    {
        users.emplace_back("admin", "123456", SUPER_ADMIN);
        users.emplace_back("cardadmin", "123456", CARD_ADMIN);
        users.emplace_back("cashier", "123456", CASHIER);
        users.emplace_back("finance", "123456", FINANCE);
    }

    if (cardTemplates.empty())
{
    cardTemplates.emplace_back("TPL001", "普通卡", 200, 10000, 0.95, 365);
    cardTemplates.emplace_back("TPL002", "银卡", 500, 20000, 0.90, 730);
    cardTemplates.emplace_back("TPL003", "金卡", 800, 50000, 0.85, 1095);
}}

bool CardSystem::login(const std::string& username, const std::string& password)
{
    for (auto& user : users)
    {
        if (user.getUsername() == username)
        {
            if (user.login(password))
            {
                currentUsername = username; 
                return true;
            }
            break;
        }
    }
    return false;
}




bool CardSystem::addUser(const User& user)
{
    for (const auto& u : users)
        if (u.getUsername() == user.getUsername()) return false;
    users.push_back(user);
    return true;
}

bool CardSystem::removeUser(const std::string& username)
{
    for (auto it = users.begin(); it != users.end(); ++it)
        if (it->getUsername() == username) { users.erase(it); return true; }
    return false;
}

bool CardSystem::modifyUser(const User& user)
{
    for (auto& u : users)
        if (u.getUsername() == user.getUsername()) { u = user; return true; }
    return false;
}

std::vector<User> CardSystem::getAllUsers()
{
    return users;
}

bool CardSystem::addCardTemplate(const CardTemplate& tpl)
{
    for (const auto& template_ : cardTemplates)
        if (template_.getTemplateId() == tpl.getTemplateId()) return false;
    cardTemplates.push_back(tpl);
    return true;
}

bool CardSystem::removeCardTemplate(const std::string& tplId)
{
    for (auto it = cardTemplates.begin(); it != cardTemplates.end(); ++it)
        if (it->getTemplateId() == tplId) { cardTemplates.erase(it); return true; }
    return false;
}

bool CardSystem::modifyCardTemplate(const CardTemplate& tpl)
{
    for (auto& template_ : cardTemplates)
        if (template_.getTemplateId() == tpl.getTemplateId()) { template_ = tpl; return true; }
    return false;
}

std::vector<CardTemplate> CardSystem::getAllCardTemplates()
{
    return cardTemplates;
}

std::string CardSystem::generateCardId()
{
    static int cardCounter = 0;
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    std::ostringstream oss;
    oss << "SC"
        << std::setw(4) << std::setfill('0') << local->tm_year + 1900
        << std::setw(2) << std::setfill('0') << local->tm_mon + 1
        << std::setw(2) << std::setfill('0') << local->tm_mday
        << std::setw(6) << std::setfill('0') << ++cardCounter;
    return oss.str();
}

ShoppingCard* CardSystem::findShoppingCard(const std::string& cardId)
{
    for (auto& card : shoppingCards)
        if (card.getCardId() == cardId) return &card;
    return nullptr;
}

bool CardSystem::createShoppingCard(const std::string& holderName, const std::string& phone, const std::string& templateId)
{
    for (const auto& tpl : cardTemplates)
    {
        if (tpl.getTemplateId() == templateId && tpl.getIsActive())
        {
            std::string cardId = generateCardId();
            std::time_t expireTime = std::time(nullptr) + tpl.getValidDays() * 24 * 60 * 60;
            shoppingCards.emplace_back(cardId, holderName, templateId, 0, phone, expireTime);
            return true;
        }
    }
    return false;
}

bool CardSystem::deleteShoppingCard(const std::string& cardId)
{
    for (auto it = shoppingCards.begin(); it != shoppingCards.end(); ++it)
        if (it->getCardId() == cardId) { shoppingCards.erase(it); return true; }
    return false;
}

bool CardSystem::modifyShoppingCard(const ShoppingCard& card)
{
    for (auto& c : shoppingCards)
        if (c.getCardId() == card.getCardId()) { c = card; return true; }
    return false;
}

std::vector<ShoppingCard> CardSystem::getAllShoppingCards()
{
    return shoppingCards;
}

bool CardSystem::addRecord(const Record& record)
{
    records.push_back(record);
    return true;
}

std::vector<Record> CardSystem::getRecordsByCardId(const std::string& cardId)
{
    std::vector<Record> result;
    for (const auto& record : records)
        if (record.getCardId() == cardId) result.push_back(record);
    return result;
}

std::vector<Record> CardSystem::getAllRecords()
{
    return records;
}

bool CardSystem::saveAllData()
{
    fileManager.saveUsers(users);
    fileManager.saveCardTemplates(cardTemplates);
    fileManager.saveShoppingCards(shoppingCards);
    fileManager.saveRecords(records);
    return true;
}

bool CardSystem::loadAllData()
{
    fileManager.loadUsers(users);
    fileManager.loadCardTemplates(cardTemplates);
    fileManager.loadShoppingCards(shoppingCards);
    fileManager.loadRecords(records);
    return true;
}

std::string CardSystem::getRoleName(Role role) const
{
    switch (role)
    {
    case SUPER_ADMIN: return "超级管理员";
    case CARD_ADMIN: return "卡管理员";
    case CASHIER: return "收银员";
    case FINANCE: return "财务人员";
    default: return "未知";
    }
}

std::string CardSystem::getStatusName(CardStatus status) const
{
    switch (status)
    {
    case NORMAL: return "正常";
    case ACTIVE: return "激活";
    case LOCK: return "冻结";
    case LOST: return "挂失";
    case EXPIRE: return "过期";
    case CANCEL: return "注销";
    default: return "未知";
    }
}

std::string CardSystem::getRecordTypeName(RecordType type) const
{
    switch (type)
    {
    case RECHARGE: return "充值";
    case CONSUME: return "消费";
    case REFUND: return "退款";
    case LOST_OP: return "挂失";
    case UNLOCK_OP: return "解除挂失";
    case TRANSFER_OUT: return "转出";
    case TRANSFER_IN: return "转入";
    case UPGRADE: return "卡片升级";  // 新增
    default: return "未知";
    }
}

std::string CardSystem::formatTime(std::time_t timestamp) const
{
    if (timestamp == 0) return "永久有效";
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
    return buffer;
}

void CardSystem::displayMenu()
{
    std::cout << "==========================================" << std::endl;
    std::cout << "              操作菜单" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "1. 开卡（创建购物卡）" << std::endl;
    std::cout << "2. 充值" << std::endl;
    std::cout << "3. 消费" << std::endl;
    std::cout << "4. 退款" << std::endl;
    std::cout << "5. 冻结卡片" << std::endl;
    std::cout << "6. 解冻卡片" << std::endl;
    std::cout << "7. 挂失卡片" << std::endl;
    std::cout << "8. 解除挂失" << std::endl;
    std::cout << "9. 查询卡片详情" << std::endl;
    std::cout << "10. 列出所有卡片" << std::endl;
    std::cout << "11. 查询交易记录" << std::endl;
    std::cout << "12. 卡片转账" << std::endl;

    if (getCurrentUser()->validate(SUPER_ADMIN) || getCurrentUser()->validate(CARD_ADMIN))
    {
        std::cout << "------------------------------" << std::endl;
        std::cout << "卡模板管理:" << std::endl;
        std::cout << "13. 添加卡模板" << std::endl;
        std::cout << "14. 修改卡模板" << std::endl;
        std::cout << "15. 删除卡模板" << std::endl;
        std::cout << "16. 查看所有卡模板" << std::endl;
    }

    if (getCurrentUser()->validate(SUPER_ADMIN))
    {
        std::cout << "------------------------------" << std::endl;
        std::cout << "用户管理:" << std::endl;
        std::cout << "17. 添加用户" << std::endl;
        std::cout << "18. 修改用户" << std::endl;
        std::cout << "19. 删除用户" << std::endl;
        std::cout << "20. 查看所有用户" << std::endl;
    }

    std::cout << "------------------------------" << std::endl;
    std::cout << "99. 保存数据" << std::endl;
    std::cout << "0. 退出登录" << std::endl;
    std::cout << "==========================================" << std::endl;
}

void CardSystem::runMainLoop()
{
    int choice = 0;
    bool exitSystem = false;
    
    while (!exitSystem)
    {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         购物卡管理系统 v1.0" << std::endl;
        std::cout << "==========================================" << std::endl;
        if (getCurrentUser())
        {
            std::cout << "当前用户: " << getCurrentUser()->getUsername() 
                      << " (" << getRoleName(getCurrentUser()->getRole()) << ")" << std::endl;
            std::cout << "==========================================" << std::endl;
            displayMenu();
        }
        else
        {
            std::cout << "1. 用户登录" << std::endl;
            std::cout << "2. 退出系统" << std::endl;
            std::cout << "==========================================" << std::endl;
        }
        std::cout << "请输入操作编号：";
        std::cin >> choice;
        if (getCurrentUser())
            handleMenuChoice(choice);
        else
            handleLoginChoice(choice);

        if (getCurrentUser() && choice == 0)
        {
            logout();
        }
        else if (!getCurrentUser() && choice == 2)
        {
            exitSystem = true;
        }

        if (!exitSystem)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n按回车键继续...";
            std::cin.get();
        }
    }
    saveAllData();
}

void CardSystem::handleLoginChoice(int choice)
{
    switch (choice)
    {
    case 1:
    {
        std::string username, password;
        std::cout << "\n请输入用户名：";
        std::cin >> username;
        std::cout << "请输入密码：";
        std::cin >> password;

        if (login(username, password))
            std::cout << "\n登录成功！" << std::endl;
        else
            std::cout << "\n用户名或密码错误！" << std::endl;
        break;
    }
    case 2:
        std::cout << "\n正在退出系统..." << std::endl;
        break;
    default:
        std::cout << "\n无效的操作编号！" << std::endl;
    }
}

void CardSystem::handleMenuChoice(int choice)
{
    switch (choice)
    {
    case 1: handleCreateCard(); break;
    case 2: handleRecharge(); break;
    case 3: handleConsume(); break;
    case 4: handleRefund(); break;
    case 5: handleFreeze(); break;
    case 6: handleUnfreeze(); break;
    case 7: handleReportLost(); break;
    case 8: handleUnlock(); break;
    case 9: handleQueryBalance(); break;
    case 10: handleViewAllCards(); break;
    case 11: handleQueryRecords(); break;
    case 12: handleTransfer(); break;
    case 13: handleAddTemplate(); break;
    case 14: handleModifyTemplate(); break;
    case 15: handleDeleteTemplate(); break;
    case 16: handleViewAllTemplates(); break;
    case 17: handleAddUser(); break;
    case 18: handleModifyUser(); break;
    case 19: handleDeleteUser(); break;
    case 20: handleViewAllUsers(); break;
    case 99: handleSaveData(); break;
    case 0: handleLogout(); break;
    default:
        std::cout << "\n无效的操作编号！" << std::endl;
    }
}

void CardSystem::handleCreateCard()
{
    std::string holderName, phone, templateId;
    double chargeMoney;
    std::cout << "\n请输入持卡人姓名：";
    std::cin >> holderName;
    std::cout << "请输入联系电话（可选）：";
    std::cin >> phone;
    std::cout << "卡类型可选：TPL001-普通卡(首充≥200) TPL002-银卡(首充≥500) TPL003-金卡(首充≥800)" << std::endl;
    std::cout << "请输入卡模板ID：";
    std::cin >> templateId;

    CardTemplate targetTpl;
    bool findTpl = false;
    for (auto& tpl : cardTemplates)
    {
        if (tpl.getTemplateId() == templateId && tpl.getIsActive())
        {
            targetTpl = tpl;
            findTpl = true;
            break;
        }
    }
    if (!findTpl)
    {
        std::cout << "\n模板不存在或已禁用，开卡失败！" << std::endl;
        return;
    }

    std::cout << "该卡最低开卡首充：" << targetTpl.getMinAmount() << " 元" << std::endl;
    std::cout << "请输入开卡充值金额：";
    std::cin >> chargeMoney;

    if (chargeMoney < targetTpl.getMinAmount())
    {
        std::cout << "\n充值金额未达到该卡最低首充要求，开卡失败！" << std::endl;
        return;
    }

    std::string cardId = generateCardId();
    std::time_t expireTime = std::time(nullptr) + targetTpl.getValidDays() * 24 * 60 * 60;
    ShoppingCard newCard(cardId, holderName, templateId, chargeMoney, phone, expireTime);
    shoppingCards.push_back(newCard);

    std::cout << "\n购物卡创建成功！" << std::endl;
    std::cout << "卡号：" << cardId << std::endl;
    std::cout << "卡类型：" << targetTpl.getTemplateName() << std::endl;
    std::cout << "当前余额：" << std::fixed << std::setprecision(2) << chargeMoney << std::endl;
}


void CardSystem::handleRecharge()
{
    if (shoppingCards.empty())
    {
        std::cout << "\n暂无购物卡，请先创建购物卡！" << std::endl;
        return;
    }
    std::string cardId, description;
    double amount;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        std::cout << "请输入充值金额：";
        std::cin >> amount;
        std::cout << "请输入备注（可选）：";
        std::cin >> description;
        if (card->recharge(amount, description))
        {
            std::cout << "\n充值成功！当前余额：" << std::fixed << std::setprecision(2) << card->getBalance() << std::endl;
            std::vector<Record> cardRecords = card->getRecords();
            if (!cardRecords.empty())
                addRecord(cardRecords.back());

            double total = card->getTotalRecharge();
            std::string upTplId = card->getAutoUpgradeTemplateId(total);
            if (!upTplId.empty())
            {
                std::string tplName;
                double discount = 1.0;
                for (auto& tpl : cardTemplates)
                {
                    if (tpl.getTemplateId() == upTplId && tpl.getIsActive())
                    {
                        tplName = tpl.getTemplateName();
                        discount = tpl.getDiscountRate();
                        break;
                    }
                }
                if (!tplName.empty())
                {
                    if (card->upgrade(upTplId, "累计充值达标自动升级为" + tplName))
                    {
                        std::cout << "\n----------------------------------------" << std::endl;
                        std::cout << "恭喜！累计充值达标，卡片自动升级为" << tplName << "！" << std::endl;
                        std::cout << "升级后折扣：" << std::fixed << std::setprecision(1) << discount * 10 << " 折" << std::endl;
                        std::cout << "----------------------------------------" << std::endl;
                        std::vector<Record> newRecords = card->getRecords();
                        if (!newRecords.empty())
                            addRecord(newRecords.back());
                    }
                }
            }
        }
        else
            std::cout << "\n充值失败！卡片状态异常或金额无效" << std::endl;
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
        std::cout << "可用卡号列表：" << std::endl;
        for (const auto& c : shoppingCards)
        {
            std::cout << "  - " << c.getCardId() << " (" << c.getHolderName() << ")" << std::endl;
        }
    }
}

void CardSystem::handleConsume()
{
    if (shoppingCards.empty())
    {
        std::cout << "\n暂无购物卡，请先开卡！" << std::endl;
        return;
    }
    std::string cardId, description;
    double originAmount = 0;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (!card)
    {
        std::cout << "\n未找到该卡号！" << std::endl;
        return;
    }

    std::cout << "请输入商品原价：";
    if (!(std::cin >> originAmount) || originAmount <= 0)
    {
        std::cout << "输入金额无效，本次消费取消！" << std::endl;
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        return;
    }

    double discount = card->getDiscount(cardTemplates);
    double realPay = originAmount * discount;

    std::cout << "当前卡片折扣：" << std::fixed << std::setprecision(1) << discount * 10 << " 折" << std::endl;
    std::cout << "卡内余额：" << std::fixed << std::setprecision(2) << card->getBalance() << std::endl;
    std::cout << "请输入消费备注：";
    std::cin >> description;
    std::cout << "原价：" << originAmount << " 元，折后应付：" << std::fixed << std::setprecision(2) << realPay << " 元" << std::endl;

    if (card->consume(realPay, description))
    {
        std::cout << "\n消费成功！剩余余额：" << std::fixed << std::setprecision(2) << card->getBalance() << std::endl;
        std::vector<Record> cardRecords = card->getRecords();
        if (!cardRecords.empty())
            addRecord(cardRecords.back());
    }
    else
    {
        std::cout << "\n消费失败，余额不足，未扣款！" << std::endl;
    }
}

void CardSystem::handleRefund()
{
    if (shoppingCards.empty())
    {
        std::cout << "\n暂无购物卡，请先创建购物卡！" << std::endl;
        return;
    }
    std::string cardId, description;
    double refundBalance;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        std::cout << "卡内当前余额：" << std::fixed << std::setprecision(2) << card->getBalance() << " 元" << std::endl;
        std::cout << "请输入申请退款的账面余额：";
        std::cin >> refundBalance;
        std::cout << "请输入备注（可选）：";
        std::cin >> description;

        double actualCash = card->getActualRefundCash(refundBalance);

        if (card->refund(refundBalance, description))
        {
            std::cout << "\n================ 退款成功 ================" << std::endl;
            std::cout << "账面扣减余额：" << std::fixed << std::setprecision(2) << refundBalance << " 元" << std::endl;
            std::cout << "实际退还现金：" << std::fixed << std::setprecision(2) << actualCash << " 元" << std::endl;
            std::cout << "卡内剩余余额：" << std::fixed << std::setprecision(2) << card->getBalance() << " 元" << std::endl;
            std::cout << "==========================================" << std::endl;
            
            std::vector<Record> cardRecords = card->getRecords();
            if (!cardRecords.empty())
                addRecord(cardRecords.back());
        }
        else
        {
            std::cout << "\n退款失败！卡片状态异常、金额无效或余额不足" << std::endl;
        }
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
    }
}

void CardSystem::handleFreeze()
{
    std::string cardId;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        if (card->freeze())
            std::cout << "\n卡片冻结成功！" << std::endl;
        else
            std::cout << "\n冻结失败！" << std::endl;
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
    }
}

void CardSystem::handleUnfreeze()
{
    std::string cardId;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        if (card->unfreeze())
            std::cout << "\n卡片解冻成功！" << std::endl;
        else
            std::cout << "\n解冻失败！" << std::endl;
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
    }
}

void CardSystem::handleReportLost()
{
    std::string cardId;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        if (card->reportLost())
            std::cout << "\n卡片挂失成功！" << std::endl;
        else
            std::cout << "\n挂失失败！卡片已注销或过期" << std::endl;
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
    }
}

void CardSystem::handleUnlock()
{
    std::string cardId;
    std::cout << "\n请输入卡号：";
    std::cin >> cardId;
    ShoppingCard* card = findShoppingCard(cardId);
    if (card)
    {
        if (card->unlock())
            std::cout << "\n卡片解除挂失成功！" << std::endl;
        else
            std::cout << "\n解除挂失失败！卡片已注销或过期" << std::endl;
    }
    else
    {
        std::cout << "\n未找到卡号：" << cardId << std::endl;
    }
}

void CardSystem::handleQueryBalance()
{
    std::string input;
    std::cout << "\n请输入卡号或持卡人姓名：";
    std::cin >> input;

    ShoppingCard* card = findShoppingCard(input);
    
    if (!card)
    {
        for (auto& c : shoppingCards)
        {
            if (c.getHolderName() == input)
            {
                card = &c;
                break;
            }
        }
    }

    if (card)
    {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "购物卡详情" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "卡号：" << card->getCardId() << std::endl;
        std::cout << "持卡人：" << card->getHolderName() << std::endl;
        std::cout << "余额：" << std::fixed << std::setprecision(2) << card->getBalance() << std::endl;
        std::cout << "状态：" << getStatusName(card->getStatus()) << std::endl;
        std::cout << "联系电话：" << (card->getPhone().empty() ? "未填写" : card->getPhone()) << std::endl;
        std::cout << "开卡日期：" << formatTime(card->getCreateTime()) << std::endl;
        std::cout << "到期日期：" << formatTime(card->getExpireTime()) << std::endl;
        std::cout << "==========================================" << std::endl;
    }
    else
    {
        std::cout << "\n未找到匹配的卡片！" << std::endl;
    }
}

void CardSystem::handleViewAllCards()
{
    auto cards = getAllShoppingCards();
    if (cards.empty())
    {
        std::cout << "\n暂无购物卡记录！" << std::endl;
        return;
    }

    std::cout << "\n共有 " << cards.size() << " 张购物卡：" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(20) << "卡号" << std::setw(15) << "持卡人" << std::setw(12) << "余额" 
              << std::setw(10) << "状态" << std::setw(15) << "到期日期" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    for (const auto& card : cards)
    {
        std::cout << std::setw(20) << card.getCardId()
                  << std::setw(15) << card.getHolderName()
                  << std::setw(12) << std::fixed << std::setprecision(2) << card.getBalance()
                  << std::setw(10) << getStatusName(card.getStatus())
                  << std::setw(15) << formatTime(card.getExpireTime()) << std::endl;
    }
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void CardSystem::handleQueryRecords()
{
    std::string cardId;
    std::cout << "\n请输入卡号（输入all查询所有）：";
    std::cin >> cardId;

    std::vector<Record> result;
    if (cardId == "all")
        result = getAllRecords();
    else
        result = getRecordsByCardId(cardId);

    if (result.empty())
    {
        std::cout << "\n暂无交易记录！" << std::endl;
        return;
    }

    std::cout << "\n交易记录列表（共 " << result.size() << " 条）：" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(20) << "交易编号" << std::setw(10) << "类型" << std::setw(12) << "金额" 
              << std::setw(12) << "余额" << std::setw(20) << "时间" << "备注" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    for (const auto& tx : result)
    {
        std::cout << std::setw(20) << tx.getRecordId()
                  << std::setw(10) << getRecordTypeName(tx.getType())
                  << std::setw(12) << std::fixed << std::setprecision(2) << tx.getAmount()
                  << std::setw(12) << std::fixed << std::setprecision(2) << tx.getBalanceAfter()
                  << std::setw(20) << formatTime(tx.getOperateTime())
                  << tx.getDescription() << std::endl;
    }
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void CardSystem::handleTransfer()
{
    std::string fromCardId, toCardId;
    double amount;
    std::cout << "\n请输入转出卡号：";
    std::cin >> fromCardId;
    std::cout << "请输入转入卡号：";
    std::cin >> toCardId;
    std::cout << "请输入转账金额：";
    std::cin >> amount;

    ShoppingCard* fromCard = findShoppingCard(fromCardId);
    ShoppingCard* toCard = findShoppingCard(toCardId);

    if (!fromCard) { std::cout << "\n转出卡不存在！" << std::endl; return; }
    if (!toCard) { std::cout << "\n转入卡不存在！" << std::endl; return; }
    if (fromCardId == toCardId) { std::cout << "\n不能向同一张卡转账！" << std::endl; return; }
    if (amount <= 0) { std::cout << "\n转账金额必须大于0！" << std::endl; return; }

    if (fromCard->consume(amount, "转账给 " + toCardId))
    {
        std::vector<Record> fromRecords = fromCard->getRecords();
        if (!fromRecords.empty())
            addRecord(fromRecords.back());

        if (toCard->recharge(amount, "接收 " + fromCardId + " 转账"))
        {
            std::vector<Record> toRecords = toCard->getRecords();
            if (!toRecords.empty())
                addRecord(toRecords.back());
            std::cout << "\n转账成功！" << std::endl;
        }
        else
        {
            fromCard->recharge(amount, "转账失败回退");
            std::cout << "\n转账失败！" << std::endl;
        }
    }
    else
    {
        std::cout << "\n转账失败！" << std::endl;
    }
}

void CardSystem::handleAddTemplate()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN) && !getCurrentUser()->validate(CARD_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string id, name;
    double minAmount, maxAmount, discountRate;
    int validDays;
    std::cout << "\n请输入模板ID：";
    std::cin >> id;
    std::cout << "请输入模板名称：";
    std::cin >> name;
    std::cout << "请输入最低充值金额：";
    std::cin >> minAmount;
    std::cout << "请输入最高充值金额：";
    std::cin >> maxAmount;
    std::cout << "请输入折扣率（1.0为无折扣）：";
    std::cin >> discountRate;
    std::cout << "请输入有效天数：";
    std::cin >> validDays;

    if (addCardTemplate(CardTemplate(id, name, minAmount, maxAmount, discountRate, validDays)))
        std::cout << "\n添加卡模板成功！" << std::endl;
    else
        std::cout << "\n添加卡模板失败！" << std::endl;
}

void CardSystem::handleModifyTemplate()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN) && !getCurrentUser()->validate(CARD_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string id;
    std::cout << "\n请输入要修改的模板ID：";
    std::cin >> id;

    for (auto& tpl : cardTemplates)
    {
        if (tpl.getTemplateId() == id)
        {
            std::string name;
            double discountRate;
            bool isActive;
            std::cout << "当前名称：" << tpl.getTemplateName() << std::endl;
            std::cout << "请输入新名称：";
            std::cin >> name;
            std::cout << "当前折扣率：" << tpl.getDiscountRate() << std::endl;
            std::cout << "请输入新折扣率：";
            std::cin >> discountRate;
            std::cout << "当前状态：" << (tpl.getIsActive() ? "启用" : "禁用") << std::endl;
            std::cout << "请输入新状态（1-启用, 0-禁用）：";
            std::cin >> isActive;

            CardTemplate newTpl(id, name, tpl.getMinAmount(), tpl.getMaxAmount(), discountRate, tpl.getValidDays());
            newTpl.setIsActive(isActive);
            if (modifyCardTemplate(newTpl))
                std::cout << "\n修改卡模板成功！" << std::endl;
            else
                std::cout << "\n修改卡模板失败！" << std::endl;
            return;
        }
    }
    std::cout << "\n未找到模板ID：" << id << std::endl;
}

void CardSystem::handleDeleteTemplate()
{
   if (!getCurrentUser()->validate(SUPER_ADMIN) && !getCurrentUser()->validate(CARD_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string id;
    std::cout << "\n请输入要删除的模板ID：";
    std::cin >> id;
    if (removeCardTemplate(id))
        std::cout << "\n删除卡模板成功！" << std::endl;
    else
        std::cout << "\n删除卡模板失败！" << std::endl;
}

void CardSystem::handleViewAllTemplates()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN) && !getCurrentUser()->validate(CARD_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    auto templates = getAllCardTemplates();
    if (templates.empty())
    {
        std::cout << "\n暂无卡模板！" << std::endl;
        return;
    }

    std::cout << "\n卡模板列表：" << std::endl;
    for (const auto& tpl : templates)
    {
        std::cout << "模板ID：" << tpl.getTemplateId() << std::endl;
        std::cout << "名称：" << tpl.getTemplateName() << std::endl;
        std::cout << "最低金额：" << tpl.getMinAmount() << std::endl;
        std::cout << "最高金额：" << tpl.getMaxAmount() << std::endl;
        std::cout << "折扣率：" << tpl.getDiscountRate() << std::endl;
        std::cout << "有效期：" << tpl.getValidDays() << "天" << std::endl;
        std::cout << "状态：" << (tpl.getIsActive() ? "启用" : "禁用") << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
}

void CardSystem::handleAddUser()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string username, password;
    int role;
    std::cout << "\n请输入用户名：";
    std::cin >> username;
    std::cout << "请输入密码：";
    std::cin >> password;
    std::cout << "请输入角色（0-超级管理员, 1-卡管理员, 2-收银员, 3-财务人员）：";
    std::cin >> role;

    if (addUser(User(username, password, static_cast<Role>(role))))
        std::cout << "\n添加用户成功！" << std::endl;
    else
        std::cout << "\n添加用户失败！" << std::endl;
}

void CardSystem::handleModifyUser()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string username;
    std::cout << "\n请输入要修改的用户名：";
    std::cin >> username;

    for (auto& user : users)
    {
        if (user.getUsername() == username)
        {
            std::string newPassword;
            int newRole;
            std::cout << "请输入新密码：";
            std::cin >> newPassword;
            std::cout << "请输入新角色（0-超级管理员, 1-卡管理员, 2-收银员, 3-财务人员）：";
            std::cin >> newRole;

            User newUser(username, newPassword, static_cast<Role>(newRole));
            if (modifyUser(newUser))
                std::cout << "\n修改用户成功！" << std::endl;
            else
                std::cout << "\n修改用户失败！" << std::endl;
            return;
        }
    }
    std::cout << "\n未找到用户名：" << username << std::endl;
}

void CardSystem::handleDeleteUser()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    std::string username;
    std::cout << "\n请输入要删除的用户名：";
    std::cin >> username;

    if (username == getCurrentUser()->getUsername())
    {
        std::cout << "\n不能删除当前登录用户！" << std::endl;
        return;
    }

    if (removeUser(username))
        std::cout << "\n删除用户成功！" << std::endl;
    else
        std::cout << "\n删除用户失败！" << std::endl;
}

void CardSystem::handleViewAllUsers()
{
    if (!getCurrentUser()->validate(SUPER_ADMIN))
    {
        std::cout << "\n权限不足！" << std::endl;
        return;
    }

    auto usersList = getAllUsers();
    std::cout << "\n用户列表：" << std::endl;
    for (const auto& user : usersList)
    {
        std::cout << "用户名：" << user.getUsername() << std::endl;
        std::cout << "密码：" << user.getPassword() << std::endl;
        std::cout << "角色：" << getRoleName(user.getRole()) << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
}

void CardSystem::handleSaveData()
{
    if (saveAllData())
        std::cout << "\n数据保存成功！" << std::endl;
    else
        std::cout << "\n数据保存失败！" << std::endl;
}

void CardSystem::handleLogout()
{
    logout();
    std::cout << "\n已退出登录！" << std::endl;
}
User* CardSystem::getCurrentUser()
{
    for (auto& user : users)
    {
        if (user.getUsername() == currentUsername)
            return &user;
    }
    return nullptr;
}
void CardSystem::logout()
{
    User* u = getCurrentUser();
    if (u)
    {
        u->logout();
    }
    currentUsername.clear();
    std::cout << "\n已退出登录！" << std::endl;
}
