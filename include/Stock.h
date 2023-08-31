//Header for Stock
#ifndef STOCK_H_
#define STOCK_H_

#include <string>
#include <map>

class Stock
{
private:
    std::string ticker;
    float value;
    float lastValue;
    float closeValue;
    float openValue;
    float dayChange;
    float percentChange; 
public:
    Stock(std::string tick, int val);
    ~Stock();

    float getValue();
    int   setValue(float val);
    float getDayChange();
    int   setDayChange(float val);
    float getPercentChange();
    int   setPercentChange(float val);
    std::string getTicker(){ return ticker; }

};

#endif