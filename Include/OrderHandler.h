#pragma once

#include "OrderBook.h"
#include "PricePoint.h"



class OrderHandler
{
    public:
        std::unordered_map<std::string , OrderBook*> m_orderBookS;
    
    public:
        std::vector<TradeReport> handleOrderMessage(Order oNew)
        {
            
            if(m_orderBookS.find(std::string(oNew.symbol)) == m_orderBookS.end())
            {
                m_orderBookS[std::string(oNew.symbol)]=new OrderBook(std::string(oNew.symbol));
                std::cout<<"Hello\n";
            }
            std::vector<TradeReport> matchedTrades;
            m_orderBookS[std::string(oNew.symbol)]->handleOrder(oNew , matchedTrades);
            m_orderBookS[std::string(oNew.symbol)]->printOrderBook();
            return matchedTrades;
        }
};
