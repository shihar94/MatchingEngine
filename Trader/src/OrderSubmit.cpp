#include "OrderSubmit.h"
#include <iostream>
#include <string>
OrderSubmit::OrderSubmit(){
    std::cout << "New order submit created" << std::endl;
    m_order.order_id = 0;
    m_order.price = 0;
    m_order.quantity = 0;
    m_order.type = ORDER_TYPE::RESET;
    strcpy(m_order.symbol , "ABCD");

}

OrderSubmit::~OrderSubmit(){
    std::cout << "NOrder Submit destructor" << std::endl;
}

Order OrderSubmit::requestOrder(std::string& clientID)
{
    orderReset();
    generateNewOrder(clientID);
    
    return m_order;
}

void OrderSubmit::orderReset()
{
    m_order.order_id += 1; //0;
    m_order.price = 0;
    m_order.quantity = 0;
    m_order.type = ORDER_TYPE::RESET;
}


void OrderSubmit::generateNewOrder(std::string& clientID)
{
    
   // m_order.order_id = m_orderId;

    std::string id = clientID + std::to_string(m_order.order_id);
    strcpy(m_order.clientOrderId , id.c_str());
    m_order.price = 78;
    m_order.quantity = 100;
    if(m_order.order_id %2 == 0)
    {   
       m_order.type = ORDER_TYPE::BUY;
    }
    else
    {
        m_order.type = ORDER_TYPE::SELL;
    }
    
    
    std::cout << m_orderId <<std::endl;
}