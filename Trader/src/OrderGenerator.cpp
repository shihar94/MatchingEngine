#include "OrderGenerator.h"

int OrderGenerator::NO_OF_CLIENTS = 0;


OrderGenerator::OrderGenerator(std::string& clientID)
{
   
    m_clientID = clientID;
    NO_OF_CLIENTS++;

    m_orderSubmitter = new OrderSubmit();
}

void OrderGenerator::init()
{

}



void OrderGenerator::start()
{

}



Order OrderGenerator::getOrder(std::string& clientID)
{
    return m_orderSubmitter->requestOrder(clientID);
}