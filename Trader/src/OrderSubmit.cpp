#include "OrderSubmit.h"
#include <iostream>
OrderSubmit::OrderSubmit(){
    std::cout << "New order submit created" << std::endl;
    m_order.order_id = 0;
    m_order.price = 0;
    m_order.quantity = 0;
    m_order.type = ORDER_TYPE::RESET;
}

OrderSubmit::~OrderSubmit(){
    std::cout << "NOrder Submit destructor" << std::endl;
}

Order OrderSubmit::requestOrder()
{
    orderReset();
    generateNewOrder();
    
    return m_order;
}

void OrderSubmit::orderReset()
{
    m_order.order_id += 1; //0;
    m_order.price = 0;
    m_order.quantity = 0;
    m_order.type = ORDER_TYPE::RESET;
}


void OrderSubmit::generateNewOrder()
{
    
   // m_order.order_id = m_orderId;
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