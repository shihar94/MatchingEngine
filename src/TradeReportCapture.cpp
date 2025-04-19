#include "TradeReportCapture.h"
#include <string.h>


TradeReport TradeReportCapture::createPFILLTradeMatches(Order& primary_order , Order& secondary_order)
{
    TradeReport tr; 
    strcpy(tr.symbol , primary_order.symbol);
    strcpy(tr.clientOrderId , primary_order.clientOrderId);
    tr.type = TRADE_MATCHES::PFILL;
    tr.quantityLeft = primary_order.quantity- secondary_order.quantity;
    tr.quantityMatched= secondary_order.quantity ;
    strcpy(tr.matchedClientOrderId, secondary_order.clientOrderId);
    tr.price = primary_order.price;
    tr.own_order_id = primary_order.order_id;
    tr.other_order_id = secondary_order.order_id;
    return tr;


}

TradeReport TradeReportCapture::createFILLTradeMatches(Order& primary_order , Order& secondary_order)
{
    TradeReport tr; 
    strcpy(tr.symbol , primary_order.symbol);
    strcpy(tr.clientOrderId , primary_order.clientOrderId);
    tr.type = TRADE_MATCHES::FILL;
    tr.quantityLeft = 0;
    tr.quantityMatched= primary_order.quantity;
    strcpy(tr.matchedClientOrderId, secondary_order.clientOrderId);
    tr.price = primary_order.price;
    tr.own_order_id = primary_order.order_id;
    tr.other_order_id = secondary_order.order_id;
    return tr;


}

TradeReport TradeReportCapture::newOrder(Order& primary_order)
{
    TradeReport tr; 
    strcpy(tr.symbol , primary_order.symbol);
    strcpy(tr.clientOrderId , primary_order.clientOrderId);
    tr.type = TRADE_MATCHES::NEW;
    tr.quantityLeft = primary_order.quantity;
    tr.quantityMatched = 0;
    strcpy(tr.matchedClientOrderId, primary_order.clientOrderId);
    tr.price = primary_order.price;
    tr.own_order_id = primary_order.order_id;
    tr.other_order_id = primary_order.order_id;

    return tr;
}