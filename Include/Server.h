#ifndef SERVER_H
#define SERVER_H

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






class Server
{
    public:
        Server(int port);
        ~Server();
        void init();
        void start();
        void loop(int clientSocket);
        void run();



    private:
        int m_serverSocket, m_clientSocket;
        int m_port;
        sockaddr_in m_hint;
        sockaddr_in m_client;
        socklen_t m_clientSize = sizeof(m_client);
        OrderBook* m_orderBook;
    


};


#endif