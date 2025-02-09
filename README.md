# MatchingEngine
- A Simple Matching Engine which accepts BUY and SELL orders and matches. Currently only supports exact price and partial fills.
-Partial fills means that an order can be matched with multiple orders, and the quantity of shares bought or sold can be less than the quantity of shares specified in the original order
---

## Building and Running The project
Building The server and running it.
```bash
$ mkdir build && cd build
$ cmake ..
$ make Matching_Engine 
$./Matching_Engine portNo
```

Building the client and running it.
```bash
$ cd Trader 
$ mkdir build && cd build
$ cmake ..
$ make Trader 
$./Trader portNo clientId
```
## Order Structure Submitted through TCP Connection
```c++

struct Order
{
    int order_id;
    int price;
    int quantity;
    ORDER_TYPE type;
};
```