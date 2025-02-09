//this is to maintain a linkedlist of orders which for a same price point
//which will arranged in time priority.

#ifndef PRICEPOINT_H    
#define PRICEPOINT_H

#include "defs.h"


//this is a node which is similar to a linkedlist node
struct OrderNode{
    Order order;
    OrderNode* next = nullptr;
};

class PricePoint
{
    private:
        OrderNode* m_head = nullptr;
        //OrderNode* m_tail;
        //double m_pricePoint;
        int m_availableOrders = 0;
    public:
        PricePoint();
        ~PricePoint();
        void addOrder(Order order,std::vector<TradeReport>& tradeReport);
        void removeOrder(Order order);
        void printOrders();
        bool matchOrder(Order& order , std::vector<TradeReport>& matchedTrades);
        int getAvailableOrders();
        TradeReport createTradeMatches(Order& m_order , Order& c_order);
        TradeReport newOrder(Order& primary_order);
};

#endif
