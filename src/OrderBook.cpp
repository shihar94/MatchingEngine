#include "OrderBook.h"
#include <iostream>

OrderBook::OrderBook()
{
    //initialize the orderbook
    std::cout << "OrderBook constructor called" << std::endl;
}


OrderBook::~OrderBook()
{

    //delete the orderbook
    std::cout << "OrderBook destructor called" << std::endl;
}

void OrderBook::addOrder(Order order)
{
    if(order.type == ORDER_TYPE::BUY)
    {
        addBuyOrder(order);
    }
    else
    {
        addSellOrder(order);
    }
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

void OrderBook::removeOrder(Order order)
{
    //remove the order from the orderbook
}   

void OrderBook::handleOrder(Order order)
{
    //handle the order
}   

void OrderBook::printOrderBook()
{
    //print the orderbook
    std::map<priceVal , PricePoint>::iterator it;
    std::cout << "BUY" << std::endl;
    for(it = m_priceBuyOrderMap.begin(); it != m_priceBuyOrderMap.end(); it++)
    {
        //std::cout << "Price: " << it->first << std::endl;
        it->second.printOrders();
    }

    std::cout << "SELL" << std::endl;

    for(it = m_priceSellOrderMap.begin(); it != m_priceSellOrderMap.end(); it++)
    {
        //std::cout << "Price: " << it->first << std::endl;
        it->second.printOrders();
    }
}   

void OrderBook::matchOrders()
{
    //match the orders
}
