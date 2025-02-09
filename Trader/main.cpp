

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
    if(argc < 3)
    {   
        std::cout << "./Trader portNo clienID" << std::endl;
        return 1;
    }
    
    
    int port = std::stoi((argv[1]));
    std::string clientId = argv[2];
    
    Client client(port ,clientId);
    client.init();
    client.start();
    client.loop();

    

    

    // sending data
    
    

    return 0;
}