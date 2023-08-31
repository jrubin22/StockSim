#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include <map>
#include "Stock.h"

class Exchange
{
private:
    std::map<std::string,Stock*> stocks;
public:
    Exchange();
    ~Exchange();
    Stock* getStock(std::string tick);
    int    insertStock(Stock* stock);
    
};

#endif