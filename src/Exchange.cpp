#include <iostream>
#include "Exchange.h"
#include "Stock.h"



Exchange::Exchange()
{
    std::cout << "Created Exchange" << std::endl;
}


Exchange::~Exchange()
{
    std::cout << "Destroyed Exchange" << std::endl;
}



Stock* Exchange::getStock(std::string tick)
{
    std::map<std::string, Stock*>::iterator it = stocks.begin();
    while (it != stocks.end())
    {
        if (it->first == tick)
        {
            return it->second;
        }
        it++;
    }
    std::cout << "Stock not in exchange" << std::endl;
    return nullptr;
}
int Exchange::insertStock(Stock* stock)
{
    std::map<std::string, Stock*>::iterator it = stocks.begin();
    while (it != stocks.end())
    {
        if (it->first == stock->getTicker())
        {
            std::cout << "Already in Exchange" << std::endl;
            return -1;
        }
        it++;
    }
    stocks[stock->getTicker()] = stock;
    return 0;
}