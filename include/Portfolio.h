// Header for Portfolio Class
#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

//STD
#include <string>
#include <map>

//Headers
// #include "stock.h"
#include "Exchange.h"

class Portfolio
{
private:
    int         uuid;
    float       cash;
    float       totValue;
    std::string name;
    std::map <std::string,int> stocks;
    Exchange* pExch;
    float calculateTotVal();
     
public:
    Portfolio(int id, std::string n);
    Portfolio(int id, std::string n, Exchange* ex);
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
    Exchange * getExchange();
    int setExchange(Exchange* ex);
};
#endif // PORTFOLIO_H_