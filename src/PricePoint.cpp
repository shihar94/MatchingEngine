#include "PricePoint.h"
#include <iostream>
#include <vector>
#include "defs.h"
PricePoint::PricePoint()
{
    //std::cout << "PricePoint constructor called for price: " << std::endl;
    
}


PricePoint::~PricePoint()
{
    //delete m_head;
}


void PricePoint::addOrder(Order order , std::vector<TradeReport>& tradeReport)
{
    /*
    std::cout << "Adding order to price point" << std::endl;
    std::cout << "Order ID: " << order.order_id << std::endl;
    std::cout << "Price: " << order.price << std::endl;
    std::cout << "Quantity: " << order.quantity << std::endl;
    std::cout << "Type: " << order.type << std::endl;*/


    OrderNode* tempNode = new OrderNode();

    tempNode -> order = order;
    tempNode -> next = nullptr;

    if(m_head == nullptr)
    {

        m_head = tempNode;
        //m_head->next  = nullptr;
    }
    else
    {   
        OrderNode* curr = m_head;

        while(curr -> next != nullptr)
        {
            curr = curr -> next;
        }
        curr -> next = tempNode;

        //m_tail = tempNode;
    }
    tradeReport.push_back(newOrder(order));
    m_availableOrders++;
}


void PricePoint::removeOrder(Order order)
{
    
}

void PricePoint::printOrders()
{
    //std::cout << "\nPrinting orders for price point\n" << std::endl;
    


    OrderNode* tempNode = m_head;
    while(tempNode != nullptr)
    {
        
        
        std::cout << "      "<<tempNode -> order.order_id <<" ";
        std::cout << "      "<<  tempNode -> order.price << " ";
        std::cout << "      "<< tempNode -> order.quantity << " ";
        std::cout << "      "<<tempNode -> order.type << " ";
        std::cout << "      "<<tempNode -> order.symbol << " ";
        std::cout << "      "<<tempNode -> order.clientOrderId << " ";
        std::cout << "      "<<tempNode -> order.prize<< " ";
        std::cout << "" << std::endl;
        tempNode = tempNode -> next;

    }   
}


bool PricePoint::matchOrder(Order& order , std::vector<TradeReport>& matchedTrades)
{

   // std::cout << "Matching order for order id: " << order.clientOrderId<< std::endl;
    if(m_availableOrders <= 0)
    {
        std::cout << "No Available Orders to be matched" << std::endl;
        return false;

    }

    //std::vector<TradeReport> matchedTrades;
    //retrieve the top order from the list first 
    OrderNode* tempNode = m_head;
    if(tempNode->order.quantity ==  order.quantity)
    {
        
        matchedTrades.push_back(createTradeMatches(order,tempNode->order));
        m_head = tempNode->next;
        
        delete tempNode;
        m_availableOrders = m_availableOrders - 1;
        
        return true;
    }
    else if(tempNode->order.quantity > order.quantity)
    {
        matchedTrades.push_back(createTradeMatches(order,tempNode->order));
        tempNode->order.quantity -= order.quantity;
        return true;
    }
    else if(tempNode->order.quantity < order.quantity) //handle the condition of partial fill
    {   
        std::cout <<"partial fill start with order quantity : " << order.quantity << std::endl;
        OrderNode* curr = m_head;

        while(order.quantity > 0 && curr != nullptr)
        {
            if(order.quantity - curr->order.quantity == 0)
            {
                matchedTrades.push_back(createTradeMatches(order,curr->order));
                order.quantity = order.quantity - curr->order.quantity;
                std::cout << "order.quantity = order.quantity - curr->order.quantity:  " << order.quantity << std::endl;
                m_head = curr->next;
                delete curr;
                m_availableOrders = m_availableOrders - 1;
                curr = m_head;
            }
            else if(order.quantity - curr->order.quantity < 0)
            {
                matchedTrades.push_back(createTradeMatches(order,curr->order));
                curr->order.quantity = curr->order.quantity - order.quantity;
                std::cout << "curr->order.quantity = curr->order.quantity - order.quantity:  " << curr->order.quantity << std::endl;
                order.quantity = 0 ;

            }else if(order.quantity - curr->order.quantity >0)
            {
                matchedTrades.push_back(createTradeMatches(order,curr->order));
                order.quantity = order.quantity - curr->order.quantity;
                std::cout << "3order.quantity = order.quantity - curr->order.quantity:  " << order.quantity  << std::endl;
                m_head = curr->next;
                delete curr;
                m_availableOrders = m_availableOrders - 1;
                curr = m_head;
            }
            std::cout <<"order quantity left " << order.quantity<< std::endl;
        }
        std::cout <<"\nfinal quantity left " << order.quantity << std::endl;
        std::cout <<"partial fill end" << std::endl;

        if(order.quantity == 0 )
        {
            return true;
        }   
    }
    return false;
}   


int PricePoint::getAvailableOrders()
{
    return m_availableOrders;
}


TradeReport PricePoint::createTradeMatches(Order& primary_order , Order& secondary_order)
{
    //given two orders create the tradereport for the matched order and return 
    //primary order is the main order which triggered the match 

    //secondary order is the other corresponding order
    TradeReport tr; 
    strcpy(tr.symbol , primary_order.symbol);
    strcpy(tr.clientOrderId , primary_order.clientOrderId);
    tr.type = TRADE_MATCHES::NEW;
    tr.quantityLeft = primary_order.quantity;
    tr.quantityMatched= primary_order.quantity -secondary_order.quantity;
    strcpy(tr.matchedClientOrderId, secondary_order.clientOrderId);
    tr.price = primary_order.price;
    tr.own_order_id = primary_order.order_id;
    tr.other_order_id = secondary_order.order_id;


}

TradeReport PricePoint::newOrder(Order& primary_order)
{
    TradeReport tr; 
    strcpy(tr.symbol , primary_order.symbol);
    strcpy(tr.clientOrderId , primary_order.clientOrderId);
    tr.type = TRADE_MATCHES::NEW;
    tr.quantityLeft = primary_order.quantity;
    tr.quantityMatched = 0;
    strcpy(tr.matchedClientOrderId, primary_order.clientOrderId);
    tr.price = primary_order.price;
    tr.own_order_id = primary_order.order_id;
    tr.other_order_id = primary_order.order_id;

    return tr;
}