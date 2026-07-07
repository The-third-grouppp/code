#include "cardtemplate.h"
#include <sstream>

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

string CardTemplate::toString() const {
    stringstream ss;
    ss << templateId << "|" << templateName << "|" << minAmount << "|" << maxAmount << "|"
       << discountRate << "|" << validDays << "|" << (isActive ? 1 : 0);
    return ss.str();
}

CardTemplate CardTemplate::fromString(const string& line) {
    stringstream ss(line);
    string id, name, token;
    double min, max, discount;
    int days, active;
    getline(ss, id, '|');
    getline(ss, name, '|');
    getline(ss, token, '|'); min = stod(token);
    getline(ss, token, '|'); max = stod(token);
    getline(ss, token, '|'); discount = stod(token);
    getline(ss, token, '|'); days = stoi(token);
    getline(ss, token, '|'); active = stoi(token);
    CardTemplate tpl(id, name, min, max, discount, days);
    tpl.setIsActive(active == 1);
    return tpl;
}