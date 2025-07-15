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
std::mutex om1;
class ME : public server
{
    public:
        ME(int port):server(port){}
        void onMessage(int socket)
        {
            Order oNew;
            oNew.order_id = 0;
            oNew.price = 0;
            oNew.quantity = 0;
            oNew.type = (ORDER_TYPE)1;
            int n = read(socket, &oNew, sizeof(Order));

            if(n == sizeof(Order) && oNew.type <=2)
            {
                std::cout<<oNew.clientOrderId <<" "<<oNew.symbol <<" " << oNew.order_id << " " << oNew.price << " "<< oNew.quantity << " " << oNew.type<< std::endl;
            //exit(1)
            }
            std::lock_guard<std::mutex> lock(om1);
            if(m_orderBookS.find(std::string(oNew.symbol)) == m_orderBookS.end())
            {
                m_orderBookS[std::string(oNew.symbol)]=new OrderBook(std::string(oNew.symbol));
                std::cout<<"Hello\n";
            }
            std::vector<TradeReport> matchedTrades;
            m_orderBookS[std::string(oNew.symbol)]->handleOrder(oNew , matchedTrades);
            uint32_t number_elements = matchedTrades.size();
            send(socket, &number_elements, sizeof(number_elements), 0);
            for(int i = 0 ; i < matchedTrades.size() ; i++)
            {
                int n = write(socket,&matchedTrades[i],sizeof(TradeReport));

            }
          
        m_orderBookS[std::string(oNew.symbol)]->printOrderBook();
        }
};