#include <iostream>
#include <sqlite3.h>

#include "Portfolio.h"
#include "Stock.h"
#include "Exchange.h"

int dbQuery(const char* query, sqlite3* db)
{
    char* err;
    int rc= sqlite3_exec(db,query ,NULL,NULL,&err);
    if (rc != SQLITE_OK)
    {
        std::cout << "ERROR IS: " << err<< std::endl;
        return -1;
    }
    return 0;
}

Portfolio* getPortfolioFromDB(sqlite3* db, const std::string name)
{
    //std::string name;
    char* err;
    sqlite3_stmt* stmt = nullptr;
    std::string query = "SELECT * FROM Portfolios WHERE name = '"+name+"'";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    int uuid;
    float cash;
    float totValue;
    if (rc != SQLITE_ROW)
    {
        std::cout << "Name does not exist in database, making new entry" <<std::endl;
        std::string query = "SELECT MAX(uuid) FROM Portfolios";
        sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
        if(sqlite3_step(stmt) == SQLITE_ROW)
        {
            int maxUUID  = sqlite3_column_int(stmt, 0);
            uuid = maxUUID+1;
            query = "INSERT INTO Portfolios (uuid, exchange, name, cash, totValue) VALUES ("+std::to_string(uuid) +" , \"MainTest\" , '" + name +"', 0,  0)";
            if (sqlite3_exec(db, query.c_str(), 0, 0, &err) != SQLITE_OK)
            {
                std::cerr << "SQL error: " << err << std::endl;
                sqlite3_free(err);
            }
        }
    }
    
    uuid     = sqlite3_column_int(stmt,0);
    cash     = sqlite3_column_double(stmt,4);
    totValue = sqlite3_column_double(stmt,5);
    sqlite3_finalize(stmt);
    Portfolio *P = new Portfolio(uuid,name);
    P->setCash(cash);
    return P;
}

int writePortfolioToDB(sqlite3 *db, Portfolio * port)
{
    char* err;
    sqlite3_stmt* stmt;
    std::string query = "UPDATE Portfolios SET cash = ?, totValue = ? WHERE name = ?";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) 
    {
        sqlite3_bind_double(stmt, 1, port->getCash());
        sqlite3_bind_double(stmt, 2, port->getTotalValue());
        sqlite3_bind_text  (stmt, 3, port->getName().c_str(), -1, NULL);
        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(NULL);
            return -1;
        }
    }
    sqlite3_finalize(stmt);
    return 0;
}


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

    std::string StockTick = "NFLX";
    Stock Netflix(StockTick, 400);
    StockTick = "AAPL";
    Stock Apple(StockTick, 175);
    StockTick="GME";
    Stock Gamestop(StockTick, 25);
    Exchange E;
    Exchange* pE = &E;
    pE->insertStock(&Netflix);
    pE->insertStock(&Apple);
    pE->insertStock(&Gamestop);
    Stock * curStock = nullptr;

    newPort->setExchange(pE);

    while(openFlag)
    {
        writePortfolioToDB(db, newPort);
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