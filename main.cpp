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
#include <ThreadQueue.h>
#include <kafka/kafkaPublisher.h>
#include <nlohmann/json.hpp>
#include "ME.h"

// for convenience
using json = nlohmann::json;


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

    ME server(p);
    server.init();
    server.run();
    

    //std::string topicName = "orders";
    //kafkaPublisher k;
    //k.produce();

    
    return 0;
}