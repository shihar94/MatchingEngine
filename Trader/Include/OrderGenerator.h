#ifndef ORDERGENERATOR_H
#define ORDERGENERATOR_H

#include "OrderSubmit.h"
#include <string>

class OrderGenerator
{
    public:
        OrderGenerator(std::string& clientID);
        ~OrderGenerator();

        void init();
        void start();
        Order getOrder(std::string& clientID);
        static int getNoOfClients()
        {
            return NO_OF_CLIENTS;
        }
        

    private:
        static int NO_OF_CLIENTS ;
        std::string m_clientID;
        OrderSubmit* m_orderSubmitter;

};


#endif