//this is to maintain a linkedlist of orders which for a same price point
//which will arranged in time priority.

#ifndef PRICEPOINT_H    
#define PRICEPOINT_H

enum ORDER_TYPE
{
    BUY  = 1 ,
    SELL = 2 
};

struct Order
{
    int order_id;
    double price;
    int quantity;
    ORDER_TYPE type;
};

//this is a node which is similar to a linkedlist node
struct OrderNode{
    Order order;
    OrderNode* next = nullptr;
};

class PricePoint
{
    private:
        PricePoint* head;
        PricePoint* tail;
    public:
        PricePoint();
        ~PricePoint();
        void addOrder(Order order);
        void removeOrder(Order order);
        void printOrders();
        Order returnOrder();
};

#endif
