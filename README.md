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
![Matching_Engine](https://github.com/user-attachments/assets/2110bc30-7dea-488a-916d-0cc4d80b2cb5)

Matching Engine consists of a server which responds to client tcp connections and has orderbooks for each symbol maintained using a hash map for each symbol. Each of those individual order books will have a two order nodes corresponding to buy and sell side for that instrument.

## Building Server and Running it.
```bash
$ mkdir build && cd build
$ cmake ..
$ make Matching_Engine 
$./Matching_Engine portNo
```
The server is able to handle multiple clients.

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
Currently in progress.
