#ifndef TRADEREPORTCAPTURE_H
#define TRADEREPORT_H

#include "defs.h"

class TradeReportCapture
{
    public:
    TradeReport createFILLTradeMatches(Order& primary_order , Order& secondary_order);
    TradeReport newOrder(Order& primary_order);
    TradeReport createPFILLTradeMatches(Order& primary_order , Order& secondary_order);
};

#endif