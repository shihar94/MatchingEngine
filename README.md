# MatchingEngine
- A Simple Matching Engine which accepts BUY and SELL orders and matches. Currently only supports exact price and partial fills.
-Partial fills means that an order can be matched with multiple orders, and the quantity of shares bought or sold can be less than the quantity of shares specified in the original order
-- Currently built on macOS M1. Developed to be handled in linux environments but not tested yet. 
---

## Project Structure 
```bash
├── CMakeLists.txt
├── Include
│   ├── OrderBook.h
│   ├── PricePoint.h
│   └── Server.h
├── README.md
├── Trader
│   ├── CMakeLists.txt
│   ├── Include
│   │   ├── Client.h
│   │   ├── OrderGenerator.h
│   │   └── OrderSubmit.h
│   ├── main.cpp
│   └── src
│       ├── Client.cpp
│       ├── OrderGenerator.cpp
│       └── OrderSubmit.cpp
├── git.bash
├── main.cpp
├── runME.bash
├── runTR.bash
└── src
    ├── OrderBook.cpp
    ├── PricePoint.cpp
    └── Server.cpp
```

## Building Server and Running it.
```bash
$ mkdir build && cd build
$ cmake ..
$ make Matching_Engine 
$./Matching_Engine portNo
```
The server is able to handle single client and currently its focussed on improving to handle multiple clients.

## Building the client and Running it.
```bash
$ cd Trader 
$ mkdir build && cd build
$ cmake ..
$ make Trader 
$./Trader portNo clientId
```
The client is a data generator programme. This can be modified to include inputs from user and submit for the server. 

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

## Testing 
--Currently in progress.