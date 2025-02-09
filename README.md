# MatchingEngine
- A Simple Matching Engine which accepts BUY and SELL orders and matches. Currently only supports exact price and partial fills.
-Partial fills means that an order can be matched with multiple orders, and the quantity of shares bought or sold can be less than the quantity of shares specified in the original order
---

## Building and Running The project
Building The server and running it.
The server is able to handle single client and currently its focussed on improving to handle multiple clients.
```bash
$ mkdir build && cd build
$ cmake ..
$ make Matching_Engine 
$./Matching_Engine portNo
```

Building the client and running it.
The client is a data generator programme. This can be modified to include inputs from user and submit for the server. 
```bash
$ cd Trader 
$ mkdir build && cd build
$ cmake ..
$ make Trader 
$./Trader portNo clientId
```
## Order Structure Submitted through TCP Connection
The order structure is as follows where the order id , price , quantity and order type will be submitted in the struct for the server.
```c++
struct Order
{
    int order_id;
    int price;
    int quantity;
    ORDER_TYPE type;
};
```

