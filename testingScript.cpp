/*
This is a executable used for debugging the orderbook to identify 
the correct operations and the correct path are used
*/

#include "OrderBook.h"
#include "defs.h"
#include <iostream>
#include <vector>

int main()
{

    OrderBook m_orderBook("ABCD");
    Order order1{1 ,1101 , 100 ,ORDER_TYPE::BUY , 11.01 , "client11" , "ABCD"};
    Order order2{1 ,1101 , 100 ,ORDER_TYPE::BUY , 11.01 , "client21" , "ABCD"};
    Order order3{1 ,1101 , 100 ,ORDER_TYPE::BUY , 11.01 , "client31" , "ABCD"}; 
    
    Order order4{1 ,1101 , 400 ,ORDER_TYPE::SELL , 11.01 , "client41" , "ABCD"};
    
    //Order order1{"client11" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
    //Order order2{"client21" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //primary order
    //Order order3{"client31" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //primary order
    
    //Order order4{"client41" , "ABCD" , 11.01 , 1 , 1101, 400 , ORDER_TYPE::SELL}; //primary order
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
}
