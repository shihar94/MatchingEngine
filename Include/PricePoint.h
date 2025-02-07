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
    int price;
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
        OrderNode* m_head = nullptr;
        //OrderNode* m_tail;
        //double m_pricePoint;
        int m_availableOrders = 0;

    public:
        PricePoint();
        ~PricePoint();
        void addOrder(Order order);
        void removeOrder(Order order);
        void printOrders();
        bool matchOrder(Order& order);
        Order returnOrder();
        int getAvailableOrders();

};

#endif
