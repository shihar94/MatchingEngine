#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Server.h"
#include "OrderBook.h"
#include <vector>

/*
ntohs -->> network to host short
*/

void printPID()
{
    pid_t pid = getpid();
    std::cout << pid << " pid\n";
}

int  main(int argc , char* argv[]){


    if(argc < 2)
    {   
        std::cout << "./Matching_Engine portNo" << std::endl;
        return 1;
    }

    OrderBook m_orderBook("ABCD");
    Order order1{"client11" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
    Order order2{"client21" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //primary order
    Order order3{"client31" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //primary order
    
    Order order4{"client41" , "ABCD" , 11.01 , 1 , 1101, 400 , ORDER_TYPE::SELL}; //primary order
    std::vector<TradeReport> matchedTrades1 , matchedTrades2 , matchedTrades3, matchedTrades4;
    m_orderBook.handleOrder(order1,matchedTrades1);
    m_orderBook.handleOrder(order2,matchedTrades2);
    m_orderBook.handleOrder(order3,matchedTrades3);

    m_orderBook.handleOrder(order4,matchedTrades4);
    m_orderBook.printOrderBook();

    std::cout <<" TR" <<std::endl;
    for(int i = 0 ; i <matchedTrades4.size() ; i++)
    {
        std::cout <<"TR id                : " << i                                      <<std::endl;
        std::cout <<"matchedTrades4.size(): " << matchedTrades4.size()                  <<std::endl;
        std::cout <<"Quantity Left        : " << matchedTrades4[i].quantityLeft         <<std::endl;
        std::cout <<"Quantity Matched     : " << matchedTrades4[i].quantityMatched      <<std::endl;
        std::cout <<"Price                : " << matchedTrades4[i].price                <<std::endl;
        std::cout <<"matchedClientOrderId : " << matchedTrades4[i].matchedClientOrderId <<std::endl;
        std::cout <<"ClientOrderId        : " << matchedTrades4[i].clientOrderId        <<std::endl;
        std::cout <<"Type                 : " << matchedTrades4[i].type                 <<std::endl;
        std::cout <<"\n";
    }   
    

    return 0;

    printPID();
    int p = std::stoi((argv[1]));   

    Server server(p);
    server.init();
    server.run();
    


    
    return 0;
}