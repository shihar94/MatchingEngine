#include "Client.h"


Client::Client(int port)
{
    m_port = port;
    m_clientSocket = socket(AF_INET , SOCK_STREAM , 0);
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
    send(m_clientSocket, message, strlen(message), 0);
    while(true)
    {
        
        /*if(fwrite(&message, 1, sizeof(message), client) != sizeof(message))
	    {
		    fprintf(stderr, "Failed to write command\n");
            
		    return 1;
	    }*/
        send(m_clientSocket, message, strlen(message), 0);
        usleep(10000* 1000);
    }
    // closing socket
}

void Client::close()
{
    //close(m_clientSocket);
}