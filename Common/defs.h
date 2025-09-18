#ifndef DEFS_H
#define DEFS_H

#include <thread>
#define ORDER_SIZE 40
#define TR_SIZE 56



enum ORDER_TYPE
{
    RESET = -1,
    BUY  = 1 ,
    SELL = 2 
};

enum TRADE_MATCHES
{
    NEW = 0,
    FILL = 1 ,
    PFILL = 2
};

struct Order
{
    //aligned appropriately to reduce the padding 0 padding currently 
    int order_id; //4bytes
    int prize; //4 bytes
    int quantity; //4 bytes 
    ORDER_TYPE type; //4 bytes 
    double price; //8 bytes
    char clientOrderId[11];  //11 bytes
    char symbol[5]; //5 bytes
};

struct TradeReport
{
    //properyly aligned to obtain 56 bytes with padding of 1 byte
    int own_order_id; //4 bytes
    int other_order_id; //4 bytes
    int quantityMatched; //4 bytes
    int quantityLeft; //4 bytes
    TRADE_MATCHES type;//4 bytes
    char symbol[5]; //5 bytes
    char matchedClientOrderId[11]; //11 bytes
    char clientOrderId[11]; //11 bytes
    double price; //8 bytes 
};

//this is a node which is similar to a linkedlist node
struct OrderNode{
    Order order;
    OrderNode* next = nullptr;
};


template<typename T, typename... A>
std::thread* clientThread(T &&func, A &&... args) noexcept 
{
    std::thread* t = new std::thread((std::forward<T>(func)),(std::forward<A>(args))...);
    return t;
}

#endif