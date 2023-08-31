//Implementation for Stock
#include "Stock.h"


float Stock::getValue()
{
    return value;
}
int   Stock::setValue(float val)
{
    if (val => 0.0f)
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
    if (value + val => 0.0f)
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