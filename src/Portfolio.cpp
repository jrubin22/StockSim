//Implementation for Portfolio Class
#include <iostream>
#include "Portfolio.h"

Portfolio::Portfolio(int id, std::string n):
    uuid(id),
    name(n)
{};

Portfolio::~Portfolio()
{
    std::cout << "Destroyed Portfolio" << std::endl;
}


int Portfolio::Buy(std::string ticker, int amt)
{
    /*TODO
        Check if ticker is valid
        Check Price of ticker
        Check Price of ticker * amt
        Subtract amt from cash (Fee?)
        Increase amount in map
    */ 

    std::cout << "Previous amount of " << ticker << " is " << stocks[ticker] << std::endl;
    stocks[ticker]+=amt;
    std::cout << "New amount of " << ticker << " is " << stocks[ticker] << std::endl;
    return 0;
}

int Portfolio::Sell(std::string ticker, int amt)
{
    /*TODO
        Check if ticker is valid
        Check if we have enough of that ticker in the map
        Check Price of ticker
        Check Price of ticker * amt
        Add amt in cash (Fee?)
        subtract amount in map
    */ 

    if (stocks[ticker] >= amt)
    {
        std::cout << "Previous amount of " << ticker << " is " << stocks[ticker] << std::endl;
        stocks[ticker]-=amt;
        std::cout << "New amount of " << ticker << " is " << stocks[ticker] << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Not enough shares of " << ticker << " Only have: " << stocks[ticker]<< std::endl;
        return -1;

    }
}


int Portfolio::setCash(float newCash)
{
    cash = newCash;
    return 0;
}

float Portfolio::getCash()
{
    return cash;
}

float Portfolio::getTotalValue()
{
    return totValue;
}

std::string Portfolio::getName()
{
    return name;
}

int Portfolio::viewStocks()
{
    std::map<std::string, int>::iterator it = stocks.begin();
    while (it != stocks.end())
    {
        std::cout << "Ticker: "<< it->first << " Amount: " << it->second << std::endl;
        it++;
    }
    return 0;
}

int Portfolio::getStockAmt(std::string ticker)
{
    if (stocks.find(ticker) == stocks.end())
        return 0;
    return stocks[ticker];
}