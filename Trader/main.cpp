#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include "OrderSubmit.h"
#include <sys/types.h>
#include <unistd.h>


void printPID()
{
    pid_t pid = getpid();
    std::cout << pid << " pid\n";
}

int main()
{

    printPID();

    OrderSubmit orderSubmit;
    Order order = orderSubmit.requestOrder();
   

   
    //std::cout << order.quantity<<std::endl;
   // return 0;



    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(54000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));



    FILE* client = fdopen(clientSocket, "r+");
	setbuf(client, NULL);

    

    // sending data
    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    while(true)
    {
        if(fwrite(&order, 1, sizeof(order), client) != sizeof(order))
	    {
		    fprintf(stderr, "Failed to write command\n");
		    return 1;
	    }
        //send(clientSocket, message, strlen(message), 0);
        usleep(10000* 1000);
    }
    // closing socket
    close(clientSocket);

    return 0;
}