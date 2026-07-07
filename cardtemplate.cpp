#include "cardtemplate.h"

CardTemplate::CardTemplate() : templateId(""), templateName(""), minAmount(0), maxAmount(0), discountRate(1.0), validDays(365), isActive(true) {}

CardTemplate::CardTemplate(string id, string name, double min, double max, double discount, int days)
    : templateId(id), templateName(name), minAmount(min), maxAmount(max), discountRate(discount), validDays(days), isActive(true) {}

string CardTemplate::getTemplateId() const
{
    return templateId;
}

string CardTemplate::getTemplateName() const
{
    return templateName;
}

double CardTemplate::getMinAmount() const
{
    return minAmount;
}

double CardTemplate::getMaxAmount() const
{
    return maxAmount;
}

double CardTemplate::getDiscountRate() const
{
    return discountRate;
}

int CardTemplate::getValidDays() const
{
    return validDays;
}

bool CardTemplate::getIsActive() const
{
    return isActive;
}

void CardTemplate::setDiscountRate(double rate)
{
    discountRate = rate;
}

void CardTemplate::setIsActive(bool active)
{
    isActive = active;
}