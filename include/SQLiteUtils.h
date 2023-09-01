#ifndef SQLITEUTILS_H_
#define SQLITEUTILS_H_

#include <iostream>
#include <sqlite3.h>

#include "Portfolio.h"
#include "Stock.h"

int dbQuery(const char* query, sqlite3* db);

Portfolio* getPortfolioFromDB(sqlite3* db, const std::string name);

int writePortfolioToDB(sqlite3 *db, Portfolio * port);

#endif