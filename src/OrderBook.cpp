#include "OrderBook.h"
#include <iostream>

OrderBook::OrderBook(std::string symbol)
{
    std::cout << "OrderBook constructor called for instrument: " << symbol << std::endl;
}

OrderBook::~OrderBook()
{
    std::cout << "OrderBook destructor called" << std::endl;
}

void OrderBook::addOrder(Order order , std::vector<TradeReport>& matchedTrades )
{
    if ((order.type = ORDER_TYPE::BUY))
    {
        addBuyOrder(order,matchedTrades);
    }
    else if ((order.type = ORDER_TYPE::SELL))
    {
        addSellOrder(order , matchedTrades);
    }
}

void OrderBook::addSellOrder(Order order , std::vector<TradeReport>& matchedTrades)
{
    double price = order.price;
    m_priceSellOrderMap[price].addOrder(order, matchedTrades);
    
}

void OrderBook::addBuyOrder(Order order, std::vector<TradeReport>& matchedTrades)
{
    double price = order.price;
    m_priceBuyOrderMap[price].addOrder(order,matchedTrades); 
}

void OrderBook::cancelOrder(Order order)
{
    //remove the order from the orderbook
    //handle cancel orders
}   

void OrderBook::handleOrder(Order& order , std::vector<TradeReport>& matchedTrades)
{
    //handle the order
    //1. check if the order is a buy or sell order
    //2. if buy order, check if there is a matching sell order
    //3. if sell order, check if there is a matching buy order
    if(order.type == ORDER_TYPE::BUY)
    {
        handleOrderHelper(order, m_priceSellOrderMap , matchedTrades);
    }
    else
    {
        handleOrderHelper(order, m_priceBuyOrderMap , matchedTrades);
    }
}   

void OrderBook::handleOrderHelper(Order& order, std::map<priceVal , PricePoint>& m_priceOrderMap , std::vector<TradeReport>& matchedTrades)
{
    double price = order.price;
    if(m_priceOrderMap.find(price) == m_priceOrderMap.end())
    {
        addOrder(order , matchedTrades);
    }
    else
    {   
        if(!m_priceOrderMap[price].availableOrders())
        {
            addOrder(order , matchedTrades);
        }
        else if(!m_priceOrderMap[price].matchOrder(order , matchedTrades))
        {
                addOrder(order , matchedTrades);
        }

    }
}

void OrderBook::printOrderBook()
{
    //print the orderbook
    std::map<priceVal , PricePoint>::iterator it;
    std::cout << "\nBUY" << std::endl;
    std::cout <<"OrderID     " << "Price    " << "  Quantity   " << " Type " << std::endl;
    std::cout << " Breaking at here\n";
    for(it = m_priceBuyOrderMap.begin(); it != m_priceBuyOrderMap.end(); it++)
    {
        it->second.printOrders();
    }
    std::cout << " Breaking at here sell\n";
    std::cout << "SELL" << std::endl;
    std::cout <<"OrderID     " << "Price    " << "  Quantity   " << " Type " << std::endl;
    for(it = m_priceSellOrderMap.begin(); it != m_priceSellOrderMap.end(); it++)
    {
        it->second.printOrders();
    }
}   


