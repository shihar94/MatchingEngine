#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Server.h"

#include "OrderBook.h"

/*
ntohs -->> network to host short
*/

void printPID()
{
    pid_t pid = getpid();
    std::cout << pid << " pid\n";
}

int  main(int argc , char* argv[]){


    if(argc < 2)
    {   
        std::cout << "./Matching_Engine portNo" << std::endl;
        return 1;
    }
    printPID();
    int p = std::stoi((argv[1]));   

    std::thread t;
    OrderBook orderBook;
    Server server(p);
    server.init();
    server.run();
    


    
    return 0;
}