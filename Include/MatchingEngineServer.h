#pragma once 

#include <MainThread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "OrderBook.h"
#include "PricePoint.h"
#include <thread> 
#include <mutex>
#include "server.h"
#include "OrderHandler.h"
#include <MatchingEngineCore.h>
//std::mutex om1;
class MatchingEngineServer : public MainThread
{

    public:
        MatchingEngineServer(int port , MatchingEngineCore* meCore) : MainThread(port)
        {
            this->meCore = meCore;
            init();
            meCore->ProcRun();
        }

        void onMessage(int socket)
        {
            
            oNew.order_id = 0;
            oNew.price = 0;
            oNew.quantity = 0;
            oNew.type = (ORDER_TYPE)1;
            int n = read(socket, &oNew, sizeof(Order));
            if(n == sizeof(Order) && oNew.type <=2)
            {
                std::cout<<oNew.clientOrderId <<" "<<oNew.symbol <<" " << oNew.order_id << " " << oNew.price << " "<< oNew.quantity << " " << oNew.type<< std::endl;
            
            }
            std::lock_guard<std::mutex> lock(om1);
            std::vector<TradeReport>  matchedTrades = orderHandler.handleOrderMessage(oNew);
            uint32_t number_elements = matchedTrades.size();
            send(socket, &number_elements, sizeof(number_elements), 0);
            
            for(int i = 0 ; i < matchedTrades.size() ; i++)
            {
                int n = write(socket,&matchedTrades[i],sizeof(TradeReport));

            }
          
        }

    private:
        map<int , int > m_ClientList;
        Order oNew;

        MatchingEngineCore* meCore;
};