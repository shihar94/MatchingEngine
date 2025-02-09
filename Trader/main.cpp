

#include "OrderSubmit.h"
#include "Client.h"

void printPID()
{
    pid_t pid = getpid();
    std::cout << pid << " pid\n";
}

int main(int argc , char* argv[])
{

    printPID();

    OrderSubmit orderSubmit;
    Order order = orderSubmit.requestOrder();
   
    if(argc < 2)
    {   
        std::cout << "./Trader portNo" << std::endl;
        return 1;
    }
    printPID();
    int port = std::stoi((argv[1]));
   
    
    Client client(port);
    client.init();
    client.start();
    client.loop();

    

    

    // sending data
    
    

    return 0;
}