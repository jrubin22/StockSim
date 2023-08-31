#include <iostream>
#include "Portfolio.h"

int main()
{
    bool openFlag = true;
    std::cout<<"Hello World"<<std::endl;
    std::cout<< "Enter Name: "<<std::endl;
    std::string name;
    std::cin >> name;
    Portfolio* newPort = nullptr;
    Portfolio port = Portfolio(10,name);
    newPort = &port;
    std::string N = newPort->getName();
    std::cout << "Name is: " << N << std::endl;
    std::cout << "Enter Default Amount: " << std::endl;
    float val;
    std::cin  >> val;
    newPort->setCash(val);
    std::cout << "Amount of cash is: " << newPort->getCash() << std::endl;
    std::string op;
    std::string tick;
    int amt = 0;

    while(openFlag)
    {
        std::cout << "What operation would you like to do with " << name <<std::endl;
        std::cout << "Buy (b), Sell (s), View (v), Exit (e) " << std::endl;
        std::cin >> op;

        if (op == "Buy" || op == "buy" || op == "b")
        {
            std::cout << "What Ticker Would you like to buy?" << std::endl;
            std::cin >> tick;
            std::cout << "How much of " << tick << " would you like to buy?" << std::endl; 
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
            std::cout << "How much of " << tick << " would you like to sell?" << std::endl; 
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
            //std::cout << "Total Account Value is: " << getTotalValue()<< std::endl;
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