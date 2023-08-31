//Implementation for Portfolio Class
#include <iostream>
#include "Portfolio.h"
#include "Exchange.h"

Portfolio::Portfolio(int id, std::string n):
    uuid(id),
    name(n),
    cash(0.0f),
    totValue(0.0f),
    pExch(nullptr)
{};

Portfolio::Portfolio(int id, std::string n, Exchange* ex):
    uuid(id),
    name(n),
    cash(0.0f),
    totValue(0.0f),
    pExch(ex)
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
    if (pExch == nullptr)
    {
        std::cout << "Not associated with exchange" << std::endl;
        return -1;
    }

    Stock *s = pExch->getStock(ticker);
    float cost = (amt)*(s->getValue());
    std::cout << "cost of " << ticker << " is: " << cost << std::endl << "Cash in account is: " << cash << std::endl;

    if (cash >= cost)
    {
        std::cout << "Is this ok? Confirm (y) or (n)" << std::endl;
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y')
        {
            std::cout << "Previous amount of " << ticker << " is " << stocks[ticker] << std::endl;
            stocks[ticker]+=amt;
            cash = cash-cost;
            std::cout << "New amount of " << ticker << " is " << stocks[ticker] << std::endl;
            return 0;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            std::cout << "OK, Cancelling Purchase" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Unknown Entry, Please enter y or n. Cancelling Purchase" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "Not enough cash in account, Cancelling Purchase" << std::endl;
        return 0;
    }
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

   if (pExch == nullptr)
    {
        std::cout << "Not associated with exchange" << std::endl;
        return -1;
    }

    Stock *s = pExch->getStock(ticker);
    float val = (amt)*(s->getValue());
    std::cout << "Value of " << ticker <<" is: " << val << std::endl << "Cash in account is: " << cash << std::endl;
    std::cout << "Shares of " << ticker << " In your Account is: " << stocks[ticker] << std::endl;
    if (stocks[ticker] >= amt)
    {
        std::cout << "Is this ok? Confirm (y) or (n)" << std::endl;
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y')
        {
            std::cout << "Previous amount of " << ticker << " is " << stocks[ticker] << std::endl;
            stocks[ticker]-=amt;
            cash = cash+val;
            std::cout << "New amount of " << ticker << " is " << stocks[ticker] << std::endl;
            return 0;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            std::cout << "OK, Cancelling Purchase" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Unknown Entry, Please enter y or n. Cancelling Purchase" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "Not enough Shares in account, Cancelling Purchase" << std::endl;
        return 0;
    }




    if (pExch == nullptr)
    {
        std::cout << "Not associated with exchange" << std::endl;
        return -1;
    }

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
    return calculateTotVal();
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

Exchange * Portfolio::getExchange()
{
    if (pExch != nullptr)
    {
        return pExch;
    }
    return nullptr;
}

int Portfolio::setExchange(Exchange* ex)
{
    pExch = ex;
    return 0;
}


//Private Methods

float Portfolio::calculateTotVal()
{
    float totalVal = cash;
    float curVal;
    Stock * curSt;
    std::map<std::string, int>::iterator it = stocks.begin();
    while (it != stocks.end())
    {
        curSt = pExch->getStock(it->first);
        curVal = (curSt->getValue()) * (it->second);
        totalVal += curVal;
        it++;
    }
    return totalVal; 
}
