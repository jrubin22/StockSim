#include <sqlite3.h>
#include <iostream>

#include "SQLiteUtils.h"
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