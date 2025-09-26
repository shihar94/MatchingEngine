#pragma once
#include <thread>
#include <server.h>
#include <WorkerThread.h>

class MainThread : public server , public TransferQueue
{
    public: 
        MainThread(int port):server(port)
        {
            init();   
            
        }

        ~MainThread()
        {
            
        }

        void ProcRun() 
        {
            //std::thread t(&MainThread::run , this);
            //t1 = std::move(t);
            //t.detach();

        }

        void stop()
        {
           
            //t1.join();
        }
        void onMessage(int socket)
        {
            
            char buffer[1024] = {0};
            int valread = read(socket, buffer, 1024);
            if (valread > 0) 
            {
                std::cout << "Received: " << buffer << std::endl;
            
            }
        }
        
    public:
        std::thread t1;
        
};