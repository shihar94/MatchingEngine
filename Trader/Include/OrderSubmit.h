#ifndef ORDERSUBMIT_H
#define ORDERSUBMIT_H

#include "defs.h"

class OrderSubmit
{
    public:
        OrderSubmit();
        ~OrderSubmit();

        Order requestOrder(std::string& clientID);

    private:
        void orderReset();
        void generateNewOrder(std::string& clientID);
        

    private:
        Order m_order;
        int m_orderId = 0;
         
    



};

#endif
