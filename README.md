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
Using google test to develop scenarios to test the orderbook. The scenarios tested in GTEST hello_test.cpp are as follows.
1. Test With OrderBook with Zero Order - Expected to receive trade report with TRADE_MATCHES::NEW type
2. Test with orderbook with single order with exact quantity expected to receive report with TRADE_MATCHES::FILL type.
3. Test with multiple orders to identify working of partial fills. Expected reports with TRADE_MATCHES::PFILL for matched orders and TRADE_MATCHES::NEW type if still quantity is left and after adding to orderbook. 
-- Test Results 
```bash 
[       OK ] OrderBookTestMatchPartialFill.BasicAssertions (0 ms)
[----------] 1 test from OrderBookTestMatchPartialFill (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 3 tests.
```

## Learning Outcomes

This can be implemented via two ways as per my understanding to handle multiple clients. 

1. Using multi threading. Each thread will handle a particular client and take care of operations accordingly. This is easy to implement but with resource constraints, scalability this is not viable solution. 
2. Use of polling and select. In this identify the socket which has sent a data and act accordingly. A single thread will manage the orderbook operations and this will prevent deadlock and data race as only thread has access to the orderbook resource. Scalable but harder to implement. This will be considered for future development. 