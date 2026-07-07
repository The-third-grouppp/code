#ifndef SHOPPINGCARD_H
#define SHOPPINGCARD_H

#include <string>
#include <vector>
#include <ctime>
#include "enums.h"
#include "record.h"

using namespace std;

// ���￨�����ࣺ��װ���ſ�Ƭ���������Ժ���Ϊ
// �����￨�ĳ�ֵ�����ѡ��˿��ʧ�������Ⱥ��Ĳ���
// ά����Ƭ״̬����ˮ��¼
class ShoppingCard
{
private:
    string cardId;         // ����
    string holderName;     // �ֿ�������
    double balance;        // ���
    CardStatus status;     // ��Ƭ״̬
    string templateId;     // �����Ŀ�ģ��ID
    time_t createTime;     // ����ʱ��
    time_t expireTime;     // ����ʱ��
    vector<Record> records; // ��ˮ��¼�б�

public:
    ShoppingCard();                                // Ĭ�Ϲ��캯��
    ShoppingCard(string id, string name, string tplId, time_t expire); // ���������캯��

    bool recharge(double amount);                  // ��ֵ�������Ƿ�ɹ�
    bool consume(double amount);                   // ���ѣ������Ƿ�ɹ�
    bool refund(double amount);                    // �˿�����Ƿ�ɹ�
    bool reportLost();                             // ��ʧ�������Ƿ�ɹ�
    bool unlock();                                 // ����/�����ʧ�������Ƿ�ɹ�
    bool cancelCard();                             // ע����Ƭ�������Ƿ�ɹ�

    string getCardId() const;         // ��ȡ����
    string getHolderName() const;     // ��ȡ�ֿ�������
    double getBalance() const;        // ��ȡ���
    CardStatus getStatus() const;     // ��ȡ��Ƭ״̬
    string getTemplateId() const;     // ��ȡ����ģ��ID
    time_t getCreateTime() const;     // ��ȡ����ʱ��
    time_t getExpireTime() const;     // ��ȡ����ʱ��
    vector<Record> getRecords() const; // ��ȡ��ˮ��¼�б�

    void setHolderName(string name);         // ���óֿ�������
    void setStatus(CardStatus newStatus);    // ���ÿ�Ƭ״̬
    void setExpireTime(time_t newExpire);    // ���ù���ʱ��

    bool isValid() const;           // ��鿨Ƭ�Ƿ���Ч��δ���ڡ�δע����
    bool canOperate() const;        // ��鿨Ƭ�Ƿ�ɲ�������Ч��δ��ʧ/������

    string toString() const;
    static ShoppingCard fromString(const string& line);
    void setBalance(double b) { balance = b; }   // 用于反序列化时恢复余额
};

#endif