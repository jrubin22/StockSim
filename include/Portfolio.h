// Header for Portfolio Class
//STD
#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <string>
#include <map>

//Headers
// #include "stock.h"

class Portfolio
{
private:
    int         uuid;
    float       cash;
    float       totValue;
    std::string name;
    std::map <std::string,int> stocks;
     
public:
    Portfolio(int id, std::string n);
    ~Portfolio();
    int Buy (std::string ticker, int amt );
    int Sell(std::string ticker,  int amt );
    //int getStocks(std::string ticker);
    int getStockAmt(std::string ticker);
    int setCash(float cash);
    float getCash();
    float getTotalValue();
    int viewStocks();
    std::string getName();
};
#endif // PORTFOLIO_H_