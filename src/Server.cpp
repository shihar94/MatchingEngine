#include "Server.h"
#include <vector>
std::mutex om;
Server::Server(int port)
{
    m_port = port;

    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_serverSocket == -1)
    {
        std::cerr << "Can't create a socket! Quiting..."<< std::endl;
        exit(1);
    }
    
}

Server::~Server()
{

}

void Server::init()
{
    m_hint.sin_family = AF_INET; 
    m_hint.sin_port = htons(m_port);
    m_hint.sin_addr.s_addr = INADDR_ANY; 
    bind(m_serverSocket, reinterpret_cast<sockaddr*>(&m_hint), sizeof(m_hint));
    listen(m_serverSocket,SOMAXCONN);
}

void Server::start()
{
    
    
    m_clientSocket = accept(m_serverSocket,reinterpret_cast<sockaddr*>(&m_client), &m_clientSize);

    std::thread* t = clientThread(&Server::loop,this, m_clientSocket);
    t->detach();
}


void Server::loop(int clientSocket)
{  

    if (clientSocket == -1)
    {
        std::cerr << "Error listening a client socket! Quiting..."<< std::endl;
        exit(1);    
    }
    // Client's remote name and service port
    char host[NI_MAXHOST]; 
    char service[NI_MAXHOST]; 

    memset(host, 0, NI_MAXHOST); 
    memset(service, 0, NI_MAXHOST);

    if(getnameinfo(reinterpret_cast<sockaddr*>(&m_client),sizeof(m_client),host, NI_MAXHOST, service, NI_MAXSERV, 0)== 0){
        std::cout << host << " connected on port " << service << std::endl;
    } 
    else 
    {
        inet_ntop(AF_INET, &m_client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(m_client.sin_port) << std::endl; 
    }

    
    while(true)
    {
        Order oNew;
        oNew.order_id = 0;
        oNew.price = 0;
        oNew.quantity = 0;
        oNew.type = (ORDER_TYPE)1;
        int n = read(m_clientSocket, &oNew, sizeof(Order));

        if(n == sizeof(Order) && oNew.type <=2)
        {
            std::cout<<oNew.clientOrderId <<" "<<oNew.symbol <<" " << oNew.order_id << " " << oNew.price << " "<< oNew.quantity << " " << oNew.type<< std::endl;
            //exit(1)
        }
        std::lock_guard<std::mutex> lock(om);
        if(m_orderBookS.find(std::string(oNew.symbol)) == m_orderBookS.end())
        {
            m_orderBookS[std::string(oNew.symbol)]=new OrderBook(std::string(oNew.symbol));
            std::cout<<"Hello\n";
        }
        std::vector<TradeReport> matchedTrades;
        m_orderBookS[std::string(oNew.symbol)]->handleOrder(oNew , matchedTrades);
        for(int i = 0 ; i < matchedTrades.size() ; i++)
        {
            int n = write(m_clientSocket,&matchedTrades[i],sizeof(TradeReport));
            
        }
          
        std::cout<<"Hello\n";
        m_orderBookS[std::string(oNew.symbol)]->printOrderBook();
    }
        
    
    
}


void Server::run()
{
    while(true)
    {
        start();
        //loop();
    }
}