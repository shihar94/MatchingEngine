#ifndef ORDERSUBMIT_H
#define ORDERSUBMIT_H

enum ORDER_TYPE
{
    BUY  = 1 ,
    SELL = 2 
};

struct Order
{
    int order_id;
    int price;
    int quantity;
    ORDER_TYPE type;
};


class OrderSubmit
{
    public:
        OrderSubmit();
        ~OrderSubmit();

        Order requestOrder();


};

#endif
