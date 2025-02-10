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
   // std::thread* t1 = clientThread(&Client::readThread,this);
    //t1->detach();
}

void Client::init()
{
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
    m_serverAddress.sin_addr.s_addr = INADDR_ANY;

}

void Client::loop()
{   
    Order order;
    while(true)
    {
        //request the command details from client 
        
        order = orderGenerator->getOrder(m_clientID);
        bool receivedAll = true;
        if(fwrite(&order, 1, sizeof(order), m_client) != sizeof(order))
	    {
		    fprintf(stderr, "Failed to send order\n");
		    exit(1);
	    }
        m_read = true;
        uint32_t number_vectors = 0;
        recv(m_clientSocket, &number_vectors, sizeof(number_vectors), 0);
        std::cout <<" Amount of TRs to receive :"  << number_vectors << std::endl;
        
        for (int i = 0 ; i < number_vectors ; i++)
        {
            TradeReport tr;
            if(fread(&tr,1,sizeof(TradeReport),m_client) != sizeof(tr))
            {
                fprintf(stderr, "Failed to read report\n");
		        exit(1);
            }   
            std::cout <<tr.clientOrderId <<" "<<tr.matchedClientOrderId << " " <<tr.other_order_id << " " <<tr.price <<std::endl;
        }
        receivedAll = true;
        usleep(100* 1000);
    }
    // closing socket
}

void Client::stop()
{
    close(m_clientSocket);
}


void Client::readThread()
{
    //signal if need to read and maintain a index for which orders were stopped and read
    while(true)
    {
        TradeReport tr;
        if(fread(&tr,1,sizeof(TradeReport),m_client) != sizeof(tr))
        {
            fprintf(stderr, "Failed to read report\n");
		    exit(1);
        }   
        std::cout <<tr.clientOrderId <<" "<<tr.matchedClientOrderId << " " <<tr.other_order_id << " " <<tr.price <<std::endl;
    }
      
}

void Client::read()
{
    while(true)
    {
        readThread();
    }
}