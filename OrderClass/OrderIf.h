/*
The purpose of this is to manage different order types 
such as Market Order , IOC order etc. 
To have a common interface so depending on the order type the correct function gets called
limit orders -- common one executes against matching if not sits in the orderbook
IOC - Immediate or cancel order - if found match if not cancel the order

*/

#pragma once
#include "defs.h"
#include<vector>
#include "TradeReportCapture.h"

class OrderIf
{
    private:
        OrderNode* m_head = nullptr;
        //OrderNode* m_tail;  //have to implement this it will make easy adding orders at the end
        //double m_pricePoint;
        int m_availableOrders = 0;


    public:
        OrderIf(){};
        ~OrderIf(){delete m_head;};
        void addOrder(Order order,std::vector <TradeReport>& tradeReport);
        void removeOrder(Order order);
        void printOrders();
        bool matchOrder(Order& order , std::vector<TradeReport>& matchedTrades);
        int getAvailableOrders(){return m_availableOrders;};
        bool availableOrders();
        TradeReportCapture trc;
};