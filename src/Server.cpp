#include "Server.h"


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
    if (m_clientSocket == -1)
    {
        std::cerr << "Error listening a client socket! Quiting..."<< std::endl;
        exit(1);    
    }

    char host[NI_MAXHOST]; // Client's remote name
    char service[NI_MAXHOST]; // Service (i.e. port) the client is connected on.

    memset(host, 0, NI_MAXHOST); // ZeroMemory(host, NI_MAXHOST);
    memset(service, 0, NI_MAXHOST);

    if(getnameinfo(reinterpret_cast<sockaddr*>(&m_client),sizeof(m_client),host, NI_MAXHOST, service, NI_MAXSERV, 0)== 0){
        std::cout << host << " connected on port " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &m_client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(m_client.sin_port) << std::endl; 
    }
    
    // close listening socket
    close(m_serverSocket);


}


void Server::loop()
{  
    char buf[4096];
    while(true)
    {
        
        memset(buf, 0, 4096);
        int bytesReceived = recv(m_clientSocket, buf, 4096, 0);
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
        send(m_clientSocket, buf, bytesReceived + 1, 0);
    }
    
}