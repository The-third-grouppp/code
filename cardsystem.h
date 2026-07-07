#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <vector>
#include "user.h"
#include "cardtemplate.h"
#include "shoppingcard.h"
#include "record.h"
#include "filemanager.h"

using namespace std;

// ϵͳ�ܵ����ࣺ�����������˵���Ȩ�ޡ�ȫ��ҵ���߼�
// ��Ϊϵͳ������(Facade)���������й���ģ��
// �ṩͳһ��ϵͳ��ں�ҵ�����
class CardSystem
{
private:
    vector<User> users;                    // �û�����
    vector<CardTemplate> cardTemplates;    // ��ģ������
    vector<ShoppingCard> shoppingCards;    // ���￨����
    vector<Record> records;                // ��ˮ��¼����
    FileManager fileManager;               // �ļ�������
    User* currentUser;                     // ��ǰ��¼�û�

public:
    CardSystem();                          // ���캯������ʼ��ϵͳ
    ~CardSystem();                         // ��������

    bool initSystem();                     // ϵͳ��ʼ�����������ݡ�����Ĭ�Ϲ���Ա�ȣ�
    bool login(string username, string password); // �û���¼
    void logout();                         // �û��ǳ�
    User* getCurrentUser();                // ��ȡ��ǰ��¼�û�

    bool addUser(const User& user);        // �����û�
    bool removeUser(const string& username); // ɾ���û�
    bool modifyUser(const User& user);     // �޸��û���Ϣ
    vector<User> getAllUsers();            // ��ȡ�����û��б�

    bool addCardTemplate(const CardTemplate& tpl); // ���ӿ�ģ��
    bool removeCardTemplate(const string& tplId);  // ɾ����ģ��
    bool modifyCardTemplate(const CardTemplate& tpl); // �޸Ŀ�ģ��
    vector<CardTemplate> getAllCardTemplates();   // ��ȡ���п�ģ���б�

    bool createShoppingCard(const string& holderName, const string& templateId); // �������￨
    bool deleteShoppingCard(const string& cardId); // ɾ�����￨
    bool modifyShoppingCard(const ShoppingCard& card); // �޸Ĺ��￨��Ϣ
    ShoppingCard* findShoppingCard(const string& cardId); // ���ݿ��Ų��ҹ��￨
    vector<ShoppingCard> getAllShoppingCards(); // ��ȡ���й��￨�б�

    bool addRecord(const Record& record);  // ������ˮ��¼
    vector<Record> getRecordsByCardId(const string& cardId); // ���ݿ��Ż�ȡ��ˮ��¼
    vector<Record> getAllRecords();       // ��ȡ������ˮ��¼

    bool saveAllData();                    // �����������ݵ��ļ�
    bool loadAllData();                    // ���ļ�������������

    void runMainLoop();                    // ����̨��ѭ������ʾ�˵��������û�����
};

#endif
