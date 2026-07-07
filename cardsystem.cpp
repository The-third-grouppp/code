#include "cardsystem.h"
#include <iostream>

CardSystem::CardSystem() : currentUser(nullptr) {
    initSystem();
}

CardSystem::~CardSystem() {
    saveAllData(); 
}

bool CardSystem::initSystem() {
    loadAllData();
    if (users.empty()) {
        users.push_back(User("admin", "123456", SUPER_ADMIN));
    }
    return true;
}

bool CardSystem::login(string username, string password) {
    for (auto& u : users) {
        if (u.getUsername() == username && u.checkPassword(password)) {
            currentUser = &u;
            return true;
        }
    }
    return false;
}

void CardSystem::logout() {
    currentUser = nullptr;
}

User* CardSystem::getCurrentUser() {
    return currentUser;
}

bool CardSystem::addUser(const User& user) {
    for (const auto& u : users) {
        if (u.getUsername() == user.getUsername()) return false; 
    }
    users.push_back(user);
    return true;
}

vector<User> CardSystem::getAllUsers() { return users; }

bool CardSystem::addCardTemplate(const CardTemplate& tpl) {
    for (const auto& t : cardTemplates) {
        if (t.getTemplateId() == tpl.getTemplateId()) return false; 
    }
    cardTemplates.push_back(tpl);
    return true;
}

vector<CardTemplate> CardSystem::getAllCardTemplates() { return cardTemplates; }

bool CardSystem::createShoppingCard(const string& holderName, const string& templateId) {
    string newCardId = "C" + to_string(time(0)); 
    time_t expire = time(0) + 365 * 24 * 3600;
    ShoppingCard newCard(newCardId, holderName, templateId, expire); 
    shoppingCards.push_back(newCard);
    return true;
}

ShoppingCard* CardSystem::findShoppingCard(const string& cardId) {
    for (auto& card : shoppingCards) {
        if (card.getCardId() == cardId) return &card;
    }
    return nullptr;
}

bool CardSystem::saveAllData() {
    fileManager.saveRecords(records);
    return true;
}

bool CardSystem::loadAllData() {
    records = fileManager.loadRecords();
    return true;
}
void CardSystem::runMainLoop() {
    bool running = true;
    while (running) {
        if (currentUser == nullptr) {
            cout << "\n=== 购物卡管理系统 ===" << endl;
            cout << "1. 登录系统" << endl;
            cout << "0. 退出系统" << endl;
            cout << "请选择: ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                string uname, pwd;
                cout << "请输入账号: "; cin >> uname;
                cout << "请输入密码: "; cin >> pwd;
                if (login(uname, pwd)) {
                    cout << "登录成功！欢迎。" << endl;
                } else {
                    cout << "登录失败，账号或密码错误。" << endl;
                }
            } else if (choice == 0) {
                running = false;
            } else {
                cout << "无效选项。" << endl;
            }
        } else {
            cout << "\n=== 操作菜单 (" << currentUser->getUsername() << ") ===" << endl;
            
            if (currentUser->getRole() == SUPER_ADMIN || currentUser->getRole() == CASHIER) {
                cout << "1. 开卡 (生成新购物卡)" << endl;
                cout << "2. 充值" << endl;
                cout << "3. 消费" << endl;
                cout << "4. 挂失" << endl;
            }
            
            cout << "8. 注销登录" << endl;
            cout << "0. 安全退出系统" << endl;
            cout << "请选择: ";
            
            int choice;
            cin >> choice;
            if (choice == 8) {
                logout();
            } else if (choice == 0) {
                running = false;
            } else if (choice == 1) {
                string name, tpl;
                cout << "输入持卡人姓名: "; cin >> name;
                cout << "输入模板ID(暂随意输入): "; cin >> tpl;
                if(createShoppingCard(name, tpl)) cout << "发卡成功！" << endl;
            } else if (choice == 2) {
                string cid; double amt;
                cout << "输入卡号: "; cin >> cid;
                cout << "输入充值金额: "; cin >> amt;
                ShoppingCard* card = findShoppingCard(cid);
                
                if (card && card->recharge(amt)) {
                    cout << "充值成功！余额: " << card->getBalance() << endl;
                    records.push_back(Record(records.size()+1, cid, RECHARGE, amt, card->getBalance(), currentUser->getUsername(), time(0), "前台充值"));
                } else {
                    cout << "充值失败(卡号不存在或状态异常)。" << endl;
                }
            } else if (choice == 3) {
                string cid; double amt;
                cout << "输入卡号: "; cin >> cid;
                cout << "输入消费金额: "; cin >> amt;
                ShoppingCard* card = findShoppingCard(cid);
                if (card && card->consume(amt)) {
                    cout << "消费成功！余额: " << card->getBalance() << endl;
                    records.push_back(Record(records.size()+1, cid, CONSUME, amt, card->getBalance(), currentUser->getUsername(), time(0), "前台消费"));
                } else {
                    cout << "消费失败(余额不足或卡已挂失)。" << endl;
                }
            } else if (choice == 4) {
                 string cid;
                 cout << "输入需要挂失的卡号: "; cin >> cid;
                 ShoppingCard* card = findShoppingCard(cid);
                 if (card && card->reportLost()) {
                     cout << "挂失成功！该卡已被冻结。" << endl;
                     records.push_back(Record(records.size()+1, cid, LOST_OP, 0, card->getBalance(), currentUser->getUsername(), time(0), "前台挂失"));
                 } else {
                     cout << "挂失失败(卡号不存在或已处于非正常状态)。" << endl;
                 }
            } else {
                cout << "暂无此功能权限。" << endl;
            }
        }
    }
}