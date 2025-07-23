#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <thread> 
#include <mutex>
#include <poll.h>
#include "OrderBook.h"
#include "PricePoint.h"
using namespace std;

struct Data
{
    int i;
    int j;
};

class server
{
    public:
        server(int port)
        {
            m_port = port;
            m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(m_serverSocket == -1)
            {
                std::cerr << "Can't create a socket! Quiting..."<< std::endl;
                exit(1);
            } 
        }
        ~server(){};
        void init();
        void run(); //this is the function where polling takes place

        //virtual functions where derived class server should implement
        //virtual functions are runtime polymorphism the actual calling will be resolved in runtime. 
        //virtual functions are alway late binding as it happens at runtime. 
        // its slower because the vptr needs to access the correct function from the vtable 
        virtual void onMessage(int clientSocket);
        virtual void onConnect();
        virtual void onDisconnect();
    
    private:
        void add_client(int client_sock);
        void del_client(std::vector<pollfd>::iterator it);
        void set_reuse_addr(int listen_sock);

    private:
        int m_serverSocket, m_clientSocket;
        int m_port;
        sockaddr_in m_hint;
        sockaddr_in m_client;
        socklen_t m_clientSize = sizeof(m_client);
        std::vector<pollfd> poll_sets;
        pollfd listen_pollfd;
    public:
        std::map<std::string , OrderBook*> m_orderBookS;
        
};