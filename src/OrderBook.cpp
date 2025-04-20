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

void OrderBook::addSellOrder(Order order , std::vector<TradeReport>& matchedTrades)
{
    double price = order.price;
    m_priceSellOrderMap[price].addOrder(order, matchedTrades);
    
}

void OrderBook::addBuyOrder(Order order, std::vector<TradeReport>& matchedTrades)
{
    //add the order to the orderbook
    //1 retrieve the price point for the map 
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
        double price = order.price;
        if(m_priceSellOrderMap.find(price) == m_priceSellOrderMap.end())
        {
            addBuyOrder(order , matchedTrades);
        }
        else
        {
            if(!m_priceSellOrderMap[price].availableOrders())
            {
                addBuyOrder(order , matchedTrades);
            }
            else if(!m_priceSellOrderMap[price].matchOrder(order , matchedTrades))
            {
                std::cout << order.quantity <<std::endl;
                addBuyOrder(order , matchedTrades);
            }
        }
    }
    else
    {
        double price = order.price;
        if(m_priceBuyOrderMap.find(price) == m_priceBuyOrderMap.end())
        {
            addSellOrder(order , matchedTrades);
        }
        else
        {   if(!m_priceBuyOrderMap[price].availableOrders())
            {
                addSellOrder(order , matchedTrades);
            }
            else if(!m_priceBuyOrderMap[price].matchOrder(order , matchedTrades)){
                addSellOrder(order , matchedTrades);
            }

        }
    }
}   


void OrderBook::handleOrderHelper(Order& order, std::map<priceVal , PricePoint>& m_priceOrderMap , std::vector<TradeReport>& matchedTrades)
{
    double price = order.price;
    if(m_priceOrderMap.find(price) == m_priceOrderMap.end())
    {
        addSellOrder(order , matchedTrades);
    }
    else
    {   
        if(!m_priceOrderMap[price].availableOrders())
        {
            addBuyOrder(order , matchedTrades);
        }
        else if(!m_priceOrderMap[price].matchOrder(order , matchedTrades))
        {
                addSellOrder(order , matchedTrades);
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


