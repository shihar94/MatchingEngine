//this is to maintain a linkedlist of orders which for a same price point
//which will arranged in time priority.

#ifndef PRICEPOINT_H    
#define PRICEPOINT_H

#include "defs.h"
#include<vector>
#include "TradeReportCapture.h"

//this is a node which is similar to a linkedlist node
struct OrderNode{
    Order order;
    OrderNode* next = nullptr;
};

class PricePoint
{
    private:
        OrderNode* m_head = nullptr;
        //OrderNode* m_tail;  //have to implement this it will make easy adding orders at the end
        //double m_pricePoint;
        int m_availableOrders = 0;
    
    private:
        bool FillTradeMatches(Order& order , std::vector<TradeReport>& matchedTrades);
    public:
        PricePoint();
        ~PricePoint();
        void addOrder(Order order,std::vector <TradeReport>& tradeReport);
        void removeOrder(Order order);
        void printOrders();
        bool matchOrder(Order& order , std::vector<TradeReport>& matchedTrades);
        int getAvailableOrders();
        bool availableOrders();
        TradeReportCapture trc;
};

#endif
