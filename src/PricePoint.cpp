#include "PricePoint.h"
#include <iostream>

PricePoint::PricePoint()
{
    //std::cout << "PricePoint constructor called for price: " << std::endl;
    
}


PricePoint::~PricePoint()
{
    //delete m_head;
}


void PricePoint::addOrder(Order order)
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
        std::cout << "    "<<(double)tempNode -> order.price << " ";
        std::cout << "          "<< tempNode -> order.quantity << " ";
        std::cout << "       "<<tempNode -> order.type << " ";
        std::cout << "" << std::endl;
        tempNode = tempNode -> next;

    }   
}


bool PricePoint::matchOrder(Order& order)
{

    std::cout << "Matching order for order id: " << order.order_id<< std::endl;
    if(m_availableOrders <= 0)
    {
        std::cout << "returning here" << std::endl;
        return false;

    }
    
    //retrieve the top order from the list first 
    OrderNode* tempNode = m_head;
    if(tempNode->order.quantity ==  order.quantity)
    {
        m_head = tempNode->next;
        std::cout << order.order_id <<" order  id matched with order id: " << tempNode->order.order_id << std::endl;
        delete tempNode;
        m_availableOrders = m_availableOrders - 1;
        
        return true;
    }
    else if(tempNode->order.quantity > order.quantity)
    {
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
                order.quantity = order.quantity - curr->order.quantity;
                std::cout << "order.quantity = order.quantity - curr->order.quantity:  " << order.quantity << std::endl;
                m_head = curr->next;
                delete curr;
                m_availableOrders = m_availableOrders - 1;
                curr = m_head;
            }
            else if(order.quantity - curr->order.quantity < 0)
            {
                curr->order.quantity = curr->order.quantity - order.quantity;
                std::cout << "curr->order.quantity = curr->order.quantity - order.quantity:  " << curr->order.quantity << std::endl;
                order.quantity = 0 ;

            }else if(order.quantity - curr->order.quantity >0)
            {
                order.quantity = order.quantity - curr->order.quantity;
                std::cout << "3order.quantity = order.quantity - curr->order.quantity:  " << order.quantity  << std::endl;
                m_head = curr->next;
                delete curr;
                m_availableOrders = m_availableOrders - 1;
                curr = m_head;
            }
            //order.quantity = order.quantity - curr->order.quantity;
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
