#include "OrderBook.h"
#include <iostream>

OrderBook::OrderBook(std::string symbol)
{
    //initialize the orderbook
    std::cout << "OrderBook constructor called for instrument: " << symbol << std::endl;
}


OrderBook::~OrderBook()
{

    //delete the orderbook
    std::cout << "OrderBook destructor called" << std::endl;
}

void OrderBook::addSellOrder(Order order)
{
    double price = order.price;

    if(m_priceSellOrderMap.find(price) != m_priceSellOrderMap.end())
    {
        m_priceSellOrderMap[price].addOrder(order);
    }
    else
    {
        m_priceSellOrderMap[price].addOrder(order);
    }
}

void OrderBook::addBuyOrder(Order order)
{
    //add the order to the orderbook
    //1 retrieve the price point for the map 

    double price = order.price;

    if(m_priceBuyOrderMap.find(price) != m_priceBuyOrderMap.end())
    {
        m_priceBuyOrderMap[price].addOrder(order);
    }
    else
    {
        m_priceBuyOrderMap[price].addOrder(order);
    }

}

void OrderBook::cancelOrder(Order order)
{
    //remove the order from the orderbook
}   

void OrderBook::handleOrder(Order& order)
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
            addBuyOrder(order);
        }
        else
        {
            if(!m_priceSellOrderMap[price].matchOrder(order)){
                std::cout << order.quantity <<std::endl;
                addBuyOrder(order);
            }
        }
    }
    else
    {
        double price = order.price;
        if(m_priceBuyOrderMap.find(price) == m_priceBuyOrderMap.end())
        {
            addSellOrder(order);
        }
        else
        {
            if(!m_priceBuyOrderMap[price].matchOrder(order)){
                addSellOrder(order);
            }

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
        std::cout << "Price: " << it->first << std::endl;
        it->second.printOrders();
    }
    std::cout << " Breaking at here sell\n";
    std::cout << "SELL" << std::endl;
    std::cout <<"OrderID     " << "Price    " << "  Quantity   " << " Type " << std::endl;
    for(it = m_priceSellOrderMap.begin(); it != m_priceSellOrderMap.end(); it++)
    {
        //std::cout << "Price: " << it->first << std::endl;
        it->second.printOrders();
    }
}   


