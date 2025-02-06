#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "OrderBook.h"

/*
ntohs -->> network to host short
*/

int  main(){
    // we don't need to initiliaze socket on MacOS

    OrderBook m_orderBook;
    //buy orders
    Order order1{1, 100.2, 10, ORDER_TYPE::BUY};
    m_orderBook.handleOrder(order1);
    m_orderBook.printOrderBook();

    //sell orders
    Order order2{2, 100.2, 10, ORDER_TYPE::SELL};
    m_orderBook.handleOrder(order2); 

    Order order3{3, 100.2, 100, ORDER_TYPE::SELL};
    m_orderBook.handleOrder(order3);

    Order order4{4, 100.2, 100, ORDER_TYPE::SELL};


    Order order5{5, 100.2, 100, ORDER_TYPE::SELL};



    //m_orderBook.handleOrder(order1);
    
    
    m_orderBook.handleOrder(order4);
    m_orderBook.handleOrder(order5);
    m_orderBook.printOrderBook();

    Order order6{6, 100.2, 200, ORDER_TYPE::BUY}; //buy match orders
    //m_orderBook.handleOrder(order6);
    //m_orderBook.printOrderBook();

    return 0;
    
    // create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        std::cerr << "Can't create a socket! Quiting..."<< std::endl;
        return -1;
    }

    // bind the ip address and port to a socket
    // this is a structure
    sockaddr_in hint;
    hint.sin_family = AF_INET; // 'cause we use v4
    hint.sin_port = htons(54000);
    hint.sin_addr.s_addr = INADDR_ANY; // could also use inet_pton...
    bind(listening, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));

    // tell that the socket is for listening
    listen(listening, SOMAXCONN);

    // wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSocket = accept(listening,reinterpret_cast<sockaddr*>(&client), &clientSize);
    if (clientSocket == -1)
    {
        std::cerr << "Error listening a client socket! Quiting..."<< std::endl;
        return -1;    
    }

    char host[NI_MAXHOST]; // Client's remote name
    char service[NI_MAXHOST]; // Service (i.e. port) the client is connected on.

    memset(host, 0, NI_MAXHOST); // ZeroMemory(host, NI_MAXHOST);
    memset(service, 0, NI_MAXHOST);

    if(getnameinfo(reinterpret_cast<sockaddr*>(&client),sizeof(client),host, NI_MAXHOST, service, NI_MAXSERV, 0)== 0){
        std::cout << host << " connected on port " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl; 
    }
    
    // close listening socket
    close(listening);

    // while loop: accept and echo message back to client
    char buf[4096];

    while(true){
        memset(buf, 0, 4096);
        // wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quiting..." << std::endl;
            break;
        }
        if (bytesReceived == 0){ // if zero bytes received
            std::cout << "Client disconnected..." << std::endl;
            break;
        }
        std::cout << std::string(buf, 0, bytesReceived) << std::endl;         
        //Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);
    }

    // close the socket
    close(clientSocket);

    // we don't need to shutdown socket on MacOS


    OrderBook orderBook;
    return 0;
}