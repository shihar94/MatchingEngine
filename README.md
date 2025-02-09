# MatchingEngine
- A Simple Matching Engine which accepts BUY and SELL orders and matches. Currently only supports exact price and partial fills.
-Partial fills means that an order can be matched with multiple orders, and the quantity of shares bought or sold can be less than the quantity of shares specified in the original order
---

## Building and Running The project
Building The server and running it
```bash
$ ./build
$ cmake ..
$ make Matching_Engine 
$./Matching_Engine portNo
```