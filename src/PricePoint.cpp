#include "PricePoint.h"
#include <iostream>

PricePoint::PricePoint()
{
    std::cout << "PricePoint constructor called for price: " << std::endl;
    
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
}


void PricePoint::removeOrder(Order order)
{
    
}

void PricePoint::printOrders()
{
    std::cout << "\nPrinting orders for price point\n" << std::endl;
    std::cout <<"OrderID     " << "Price    " << "  Quantity   " << " Type " << std::endl;


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

Order PricePoint::returnOrder()
{
    
}