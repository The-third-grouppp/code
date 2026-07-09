#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include <string>

class CardTemplate
{
private:
    std::string templateId;
    std::string templateName;
    double minAmount;
    double maxAmount;
    double discountRate;
    int validDays;
    bool isActive;

public:
    CardTemplate();
    CardTemplate(const std::string& id, const std::string& name, double min, double max, double discount, int days);

    std::string getTemplateId() const;
    std::string getTemplateName() const;
    double getMinAmount() const;
    double getMaxAmount() const;
    double getDiscountRate() const;
    int getValidDays() const;
    bool getIsActive() const;

    void setDiscountRate(double rate);
    void setIsActive(bool active);
};

#endif
