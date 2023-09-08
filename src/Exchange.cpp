#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "Exchange.h"
#include "Stock.h"

static std::vector<std::string> loadTickers(const std::string& fileName)
{
    std::vector<std::string> ticks;
    std::ifstream file(fileName);

    std::string line;
    std::getline(file, line);

    while(std::getline(file,line))
    {
        ticks.push_back(line);
    }
    return ticks;
}

Exchange::Exchange()
{
    std::cout << "Created Exchange" << std::endl;
};

Exchange::Exchange(const std::string& TickerList)
{
    std::cout << "Created Exchange with data from " << TickerList << std::endl;
    std::vector<std::string> tickers = loadTickers(TickerList);
    Stock * curStock;
    //Use random until we have real values
    std::random_device rd;
    //initialize random gen 
    std::mt19937 gen(rd());
    float val;
    for (const auto& ticker : tickers)
    {
        //TODO Get value of the stock
        std::uniform_real_distribution<> dist(0.0f,500.0f);
        val = dist(gen);
        curStock = new Stock(ticker, val);
        insertStock(curStock);
        val += 5.0f;
    }
};


Exchange::~Exchange()
{
    std::cout << "Destroyed Exchange" << std::endl;
};



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