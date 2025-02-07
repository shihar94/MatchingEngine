#include "OrderSubmit.h"
#include <iostream>
OrderSubmit::OrderSubmit(){
    std::cout << "New order submit created" << std::endl;
}

OrderSubmit::~OrderSubmit(){
    std::cout << "NOrder Submit destructor" << std::endl;
}

Order OrderSubmit::requestOrder()
{
    Order order1{78, 102, 10, ORDER_TYPE::BUY};
    return order1;
}