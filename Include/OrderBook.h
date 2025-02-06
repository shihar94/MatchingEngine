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
        void addOrder(Order order);
        void removeOrder(Order order);
        void handleOrder(Order order);
        void printOrderBook();
        void matchOrders();

        


    private:
        std::map<priceVal , PricePoint> priceOrderMap;
};




#endif // ORDERBOOK_H