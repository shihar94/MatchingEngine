#include <gtest/gtest.h>
#include "OrderBook.h"
#include "defs.h"

/*
First test 
Order Book Matching with exact single order only

struct Order
{
    char clientOrderId[11];
    char symbol[4];
    double price;
    int order_id;
    int prize;
    int quantity;
    ORDER_TYPE type;
};
*/


// Test matches with no order 
TEST(OrderBookTestNoMatch,BasicAssertions)
{
  OrderBook m_orderBook("ABCD"); 
  Order order{"client11" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY};
  std::vector<TradeReport> matchedTrades;
  m_orderBook.handleOrder(order,matchedTrades);
  
  std::string matched_mClientOrderID = matchedTrades[0].matchedClientOrderId;
  std::string matched_ClientOrderID = matchedTrades[0].clientOrderId;
  std::string symbol = matchedTrades[0].symbol;

  TradeReport expected{"ABCD" , "client11" , "client11" , 11.01 , 1 , 1 , 0 , 100 , TRADE_MATCHES::NEW};
  //the tests to check if the received tr is correct
  EXPECT_EQ(1 , matchedTrades.size()); //validate the size to see amount of TR received
  EXPECT_EQ(expected.quantityLeft, matchedTrades[0].quantityLeft);
  EXPECT_EQ(expected.price, matchedTrades[0].price);
  EXPECT_EQ(expected.quantityMatched, matchedTrades[0].quantityMatched);
  EXPECT_EQ(expected.type, matchedTrades[0].type);
  EXPECT_EQ(matched_mClientOrderID, "client11");
  EXPECT_EQ(matched_ClientOrderID, "client11");
  EXPECT_EQ(symbol, "ABCD");
}


//test matches with single order
TEST(OrderBookTestSingleMatch,BasicAssertions)
{
  OrderBook m_orderBook("ABCD"); 
  Order order1{"client11" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
  Order order2{"client21" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::SELL}; //primary order
  std::vector<TradeReport> matchedTrades1;
  m_orderBook.handleOrder(order1,matchedTrades1);
  std::vector<TradeReport> matchedTrades2;
  m_orderBook.handleOrder(order2,matchedTrades2);
  
  std::string matched_mClientOrderID = matchedTrades2[0].matchedClientOrderId;
  std::string matched_ClientOrderID = matchedTrades2[0].clientOrderId;
  std::string symbol = matchedTrades2[0].symbol;
  //expect primary order tr
  TradeReport expected{"ABCD" , "client21" , "client11" , 11.01 , 1 , 1 , 100 , 0 , TRADE_MATCHES::FILL};
  //the tests to check if the received tr is correct
  EXPECT_EQ(1 , matchedTrades2.size()); //validate the size to see amount of TR received
  EXPECT_EQ(expected.quantityLeft, matchedTrades2[0].quantityLeft);
  EXPECT_EQ(expected.price, matchedTrades2[0].price);
  EXPECT_EQ(expected.quantityMatched, matchedTrades2[0].quantityMatched);
  EXPECT_EQ(expected.type, matchedTrades2[0].type);
  EXPECT_EQ(matched_mClientOrderID, "client11");
  EXPECT_EQ(matched_ClientOrderID, "client21");
  EXPECT_EQ(symbol, "ABCD");
}


TEST(OrderBookTestMatchPartialFill , BasicAssertions)
{
  OrderBook m_orderBook("ABCD");
  Order order1{"client11" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
  Order order2{"client21" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
  Order order3{"client31" , "ABCD" , 11.01 , 1 , 1101, 100 , ORDER_TYPE::BUY}; //secondary order
    
  Order order4{"client41" , "ABCD" , 11.01 , 1 , 1101, 400 , ORDER_TYPE::SELL}; //primary order

  std::vector<TradeReport> matchedTrades1 , matchedTrades2 , matchedTrades3, matchedTrades4;
  m_orderBook.handleOrder(order1,matchedTrades1);
  m_orderBook.handleOrder(order2,matchedTrades2);
  m_orderBook.handleOrder(order3,matchedTrades3);

  m_orderBook.handleOrder(order4,matchedTrades4);
  m_orderBook.printOrderBook();

  EXPECT_EQ(4 , matchedTrades4.size()); //validate the size to see amount of TR received
  
  TradeReport expected1{"ABCD" , "client11" , "client41" , 11.01 , 1 , 1 , 100 , 300 , TRADE_MATCHES::PFILL};
  TradeReport expected2{"ABCD" , "client21" , "client41" , 11.01 , 1 , 1 , 100 , 200 , TRADE_MATCHES::PFILL};
  TradeReport expected3{"ABCD" , "client31" , "client41" , 11.01 , 1 , 1 , 100 , 100 , TRADE_MATCHES::PFILL};
  TradeReport expected4{"ABCD" , "client41" , "client41" , 11.01 , 1 , 1 ,   0 , 100 , TRADE_MATCHES::NEW};
  
  EXPECT_EQ(expected1.quantityLeft, matchedTrades4[0].quantityLeft);
  EXPECT_EQ(expected1.price, matchedTrades4[0].price);
  EXPECT_EQ(expected1.quantityMatched, matchedTrades4[0].quantityMatched);
  EXPECT_EQ(expected1.type, matchedTrades4[0].type);
  EXPECT_EQ(std::string(matchedTrades4[0].matchedClientOrderId), "client11");
  EXPECT_EQ(std::string(matchedTrades4[0].clientOrderId), "client41");
  EXPECT_EQ(std::string(matchedTrades4[0].symbol), "ABCD");


  EXPECT_EQ(expected2.quantityLeft, matchedTrades4[1].quantityLeft);
  EXPECT_EQ(expected2.price, matchedTrades4[1].price);
  EXPECT_EQ(expected2.quantityMatched, matchedTrades4[1].quantityMatched);
  EXPECT_EQ(expected2.type, matchedTrades4[1].type);
  EXPECT_EQ(std::string(matchedTrades4[1].matchedClientOrderId), "client21");
  EXPECT_EQ(std::string(matchedTrades4[1].clientOrderId), "client41");
  EXPECT_EQ(std::string(matchedTrades4[1].symbol), "ABCD");

  EXPECT_EQ(expected3.quantityLeft, matchedTrades4[2].quantityLeft);
  EXPECT_EQ(expected3.price, matchedTrades4[2].price);
  EXPECT_EQ(expected3.quantityMatched, matchedTrades4[2].quantityMatched);
  EXPECT_EQ(expected3.type, matchedTrades4[2].type);
  EXPECT_EQ(std::string(matchedTrades4[2].matchedClientOrderId), "client31");
  EXPECT_EQ(std::string(matchedTrades4[2].clientOrderId), "client41");
  EXPECT_EQ(std::string(matchedTrades4[2].symbol), "ABCD");

  EXPECT_EQ(expected4.quantityLeft, matchedTrades4[3].quantityLeft);
  EXPECT_EQ(expected4.price, matchedTrades4[3].price);
  EXPECT_EQ(expected4.quantityMatched, matchedTrades4[3].quantityMatched);
  EXPECT_EQ(expected4.type, matchedTrades4[3].type);
  EXPECT_EQ(std::string(matchedTrades4[3].matchedClientOrderId), "client41");
  EXPECT_EQ(std::string(matchedTrades4[3].clientOrderId), "client41");
  EXPECT_EQ(std::string(matchedTrades4[3].symbol), "ABCD");


}
