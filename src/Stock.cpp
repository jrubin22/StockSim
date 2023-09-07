//Implementation for Stock
#include <iostream>
#include "Stock.h"


Stock::Stock(std::string tick, float val):
ticker(tick),
value(val),
lastValue(0.0f),
closeValue(0.0f),
openValue(0.0f),
dayChange(0.0f),
percentChange(0.0f)
{
};

Stock::~Stock()
{
    std::cout << "Destroyed Stock" << std::endl;
}

float Stock::getValue()
{
    return value;
}
int   Stock::setValue(float val)
{
    if (val >= 0.0f)
    {
        value = val;
        return 0;
    }
    else
    {
        std::cout << "Invalid Value " << std::endl;
        return -1;
    }
    return -1;
}
float Stock::getDayChange()
{
    return dayChange;
}
int   Stock::setDayChange(float val)
{
    //TODO Change this to openValue + val
    if (value + val >= 0.0f)
    {
        dayChange = val;
        return 0;
    }
    else
    {
        std::cout << "Invalid Value " << std::endl;
        return -1;
    }
    return -1;
}
float Stock::getPercentChange()
{
    return percentChange;
}
int   Stock::setPercentChange(float val)
{
    if (val > -100.0f)
    {
        percentChange = val;
        return 0;
    }
    else
    {
        std::cout << "Invalid Value " << std::endl;
        return -1;
    }
    return -1;
}