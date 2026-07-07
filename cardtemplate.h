#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include <string>

using namespace std;

// 卡模板类：封装卡类型属性与模板操作
// 定义购物卡的模板信息，如最低/最高金额、折扣率、有效期等
// 创建购物卡时基于模板生成具体卡片
class CardTemplate
{
private:
    string templateId;       // 模板ID
    string templateName;     // 模板名称（如：金卡、银卡、普通卡）
    double minAmount;        // 最低充值金额
    double maxAmount;        // 最高充值金额
    double discountRate;     // 折扣率（1.0为无折扣）
    int validDays;           // 有效天数
    bool isActive;           // 是否启用

public:
    CardTemplate();                                           // 默认构造函数
    CardTemplate(string id, string name, double min, double max, double discount, int days); // 带参数构造函数

    string getTemplateId() const;       // 获取模板ID
    string getTemplateName() const;     // 获取模板名称
    double getMinAmount() const;        // 获取最低充值金额
    double getMaxAmount() const;        // 获取最高充值金额
    double getDiscountRate() const;     // 获取折扣率
    int getValidDays() const;           // 获取有效天数
    bool getIsActive() const;           // 获取启用状态

    void setDiscountRate(double rate);  // 设置折扣率
    void setIsActive(bool active);      // 设置启用状态

    string toString() const;
    static CardTemplate fromString(const string& line);
};

#endif
