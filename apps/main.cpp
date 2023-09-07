#include <iostream>
#include <sqlite3.h>

#include "SQLiteUtils.h"
#include "Portfolio.h"
#include "Stock.h"
#include "Exchange.h"



int main()
{
    sqlite3* db;
    sqlite3_open("db/mydb.db", &db);
    std::string query = "SELECT * FROM port";
    dbQuery(query.c_str(), db);
    bool openFlag = true;
    std::cout<< "Enter Name: "<<std::endl;
    std::string name;
    std::cin >> name;
    Portfolio* newPort = getPortfolioFromDB(db, name);
    //Portfolio port = Portfolio(10,name);
    //newPort = &port;
    std::string N = newPort->getName();
    std::cout << "Name is: " << N << std::endl;
    if (newPort->getCash() == 0.0f)
    {
        //std::cout << "Default Cash is: "<<newPort->getCash()<<std::endl;
        std::cout << "Enter Default Amount: " << std::endl;
        float val;
        std::cin  >> val;
        newPort->setCash(val);
    }
    std::cout << "Amount of cash is: " << newPort->getCash() << std::endl;
    std::string op;
    std::string tick;
    int amt = 0;

    // std::string StockTick = "NFLX";
    // Stock Netflix(StockTick, 400);
    // StockTick = "AAPL";
    // Stock Apple(StockTick, 175);
    // StockTick="GME";
    // Stock Gamestop(StockTick, 25);
    Exchange E("db/tickers.csv");
    Exchange* pE = &E;
    // pE->insertStock(&Netflix);
    // pE->insertStock(&Apple);
    // pE->insertStock(&Gamestop);
    Stock * curStock = nullptr;

    newPort->setExchange(pE);
    writePortfolioToDB(db, newPort);
    getStocksFromDB(db,newPort);
    writeStocksToDB(db, newPort);


    while(openFlag)
    {
        writePortfolioToDB(db, newPort);
        writeStocksToDB(db, newPort);
        curStock == nullptr;
        std::cout << "What operation would you like to do with " << name <<std::endl;
        std::cout << "Buy (b), Sell (s), View (v), Exit (e) " << std::endl;
        std::cin >> op;

        if (op == "Buy" || op == "buy" || op == "b")
        {
            std::cout << "What Ticker Would you like to buy?" << std::endl;
            std::cin >> tick;
            curStock = pE->getStock(tick);
            if (curStock == nullptr)
            {
                std::cout << "That stock is not on the exchange, please try again" << std::endl;
                continue;
            }
            std::cout << "How much of " << tick << " would you like to buy?" << std::endl;             
            std::cout << "Cost of " << tick << " is: $" << curStock->getValue()<< std::endl;
            // TODO "You can afford x amt";
            std::cin >> amt;
            while (std::cin.fail())
            {
                std::cout << "Need to input an integer" <<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> amt;
            }
            newPort->Buy(tick,amt);
            continue;
        }
        else if (op == "Sell" || op == "sell" || op == "s")
        {
            std::cout << "What Ticker Would you like to sell?" << std::endl;
            std::cin >> tick;
            curStock = pE->getStock(tick);
            if (curStock == nullptr)
            {
                std::cout << "That stock is not on the exchange, please try again" << std::endl;
                continue;
            }
            std::cout << "How much of " << tick << " would you like to sell?" << std::endl;             
            std::cout << "Cost of " << tick << " is: $" << curStock->getValue()<< std::endl;
            // TODO "You can afford x amt";
            std::cin >> amt;
            while (std::cin.fail())
            {
                std::cout << "Need to input an integer" <<std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> amt;
            }
            newPort->Sell(tick,amt);
            continue;
        }
        else if (op == "View" || op == "view" || op == "v")
        {
            std::cout << "Total Account Value is: " << newPort->getTotalValue()<< std::endl;
            std::cout << "Total Cash is: " << newPort->getCash()<< std::endl;
            newPort->viewStocks();
            continue;
        }
        else if (op == "Exit" || op == "exit" || op == "e")
        {
            openFlag = false;
            continue;
        }
        else
        {
            std::cout << "Operation not supported" << std::endl;
            continue;
        }
    }



    return 0;
}