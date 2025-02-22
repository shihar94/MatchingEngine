//MAIN MATCHING ENGINE EXECUTABLE FILE

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Server.h"
#include "OrderBook.h"
#include <vector>

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

    Server server(p);
    server.init();
    server.run();
    


    
    return 0;
}