#ifndef DEFS_H
#define DEFS_H

#include <thread>

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
    char clientOrderId[11];
    char symbol[5];
    double price;
    int order_id;
    int prize;
    int quantity;
    ORDER_TYPE type;
};

struct TradeReport
{
    char symbol[5];
    char matchedClientOrderId[11];
    char clientOrderId[11];
    double price;
    int own_order_id;
    int other_order_id;
    int quantityMatched;
    int quantityLeft;
    TRADE_MATCHES type;
};



template<typename T, typename... A>
inline auto clientThread(T &&func, A &&... args) noexcept 
{
    auto t = new std::thread((std::forward<T>(func)),(std::forward<A>(args))...);
    //using namespace std::literals::chrono_literals;
    //std::this_thread::sleep_for(1s);

    return t;
}

#endif