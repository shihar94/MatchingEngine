#include "Client.h"


Client::Client(int port , std::string& clientID)
{
    m_port = port;
    m_clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    m_clientID = clientID;
    orderGenerator = new OrderGenerator(m_clientID);
   
}

Client::~Client()
{

}


void Client::start()
{
    connect(m_clientSocket, (struct sockaddr*)&m_serverAddress,sizeof(m_serverAddress));
    m_client = fdopen(m_clientSocket, "r+");
	setbuf(m_client, NULL);
}

void Client::init()
{
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
    m_serverAddress.sin_addr.s_addr = INADDR_ANY;

}

void Client::loop()
{   
    const char* message = "Hello, server!";
    //send(m_clientSocket, message, strlen(message), 0);
    Order order;
    while(true)
    {
        //request the command details from client 

        order = orderGenerator->getOrder();
        
        if(fwrite(&order, 1, sizeof(order), m_client) != sizeof(order))
	    {
		    fprintf(stderr, "Failed to write command\n");
		    exit(1);
	    }
        //send(m_clientSocket, message, strlen(message), 0);
        usleep(1000* 1000);
    }
    // closing socket
}

void Client::stop()
{
    close(m_clientSocket);
}