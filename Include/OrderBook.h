#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "PricePoint.h"
#include <map>
//this class will maintain the orderbook for a particular stock.
//for each price point it will maintain a linkedlist of orders which 
//price point lists 

using priceVal = double;

class OrderBook
{

    public:
        OrderBook();
        ~OrderBook();


        void cancelOrder(Order order);
        void handleOrder(Order& order);
        void printOrderBook();

    private:

        void addBuyOrder(Order order);
        void addSellOrder(Order order);

    private:

        std::map<priceVal , PricePoint> m_priceBuyOrderMap;
        std::map<priceVal , PricePoint> m_priceSellOrderMap;

};




#endif // ORDERBOOK_H