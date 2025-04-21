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
        OrderBook(std::string symbol);
        ~OrderBook();
        void handleOrder(Order& order , std::vector<TradeReport>& matchedTrades);
        void printOrderBook();
        

    private:
        void cancelOrder(Order order);
        void addBuyOrder(Order order , std::vector<TradeReport>& matchedTrades);
        void addSellOrder(Order order, std::vector<TradeReport>& matchedTrades);
        void handleOrderHelper(Order& order, std::map<priceVal , PricePoint>& m_priceOrderMap , std::vector<TradeReport>& matchedTrades);
        void addOrder(Order order , std::vector<TradeReport>& matchedTrades );
    
    private:
        std::map<priceVal , PricePoint> m_priceBuyOrderMap;
        std::map<priceVal , PricePoint> m_priceSellOrderMap;

};

#endif // ORDERBOOK_H