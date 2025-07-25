#include "server.h"
void server::init()
{
    m_hint.sin_family = AF_INET; 
    m_hint.sin_port = htons(m_port);
    m_hint.sin_addr.s_addr = INADDR_ANY; 
    set_reuse_addr(m_serverSocket);

    if(bind(m_serverSocket, reinterpret_cast<sockaddr*>(&m_hint), sizeof(m_hint)) < 0)
    {
        std::cerr << "Bind Failed" << std::endl;
        exit(1);
    }

    if(listen(m_serverSocket,SOMAXCONN) < 0)
    {
        perror("listen() failed");
        exit(1);
    }

    listen_pollfd.fd = m_serverSocket;
    listen_pollfd.events = POLLIN;
    poll_sets.push_back(listen_pollfd);
}

void server::add_client(int client_sock)
{
    pollfd client_pollfd;
    client_pollfd.fd = client_sock;
    client_pollfd.events = POLLIN;
    poll_sets.push_back(client_pollfd);
    //print_conn(client_sock);
    printf("now_client_num: %u\n", (unsigned int)poll_sets.size()-1);
}

void server::del_client(std::vector<pollfd>::iterator it)
{
    poll_sets.erase(it);
    //print_dconn(it->fd);
    close(it->fd);
    printf("now_client_num: %u\n", (unsigned int)poll_sets.size()-1);
}

//this should poll
void server::run()
{
    while(1)
    {
        int ret = poll((pollfd *)&poll_sets[0], (unsigned int)poll_sets.size(), -1);
        if (ret <= 0)
        {
        // timeout is error
            perror("poll error");
            exit(1);
        }
        // check every pool in the set
        std::vector<pollfd>::iterator it;
        std::vector<pollfd>::iterator end = poll_sets.end();
        for (it = poll_sets.begin(); it != end; it++)
        {
            std::cout << "Running......." << std::endl;
            if (it->revents & POLLIN)
            {   
                if (it->fd == m_serverSocket)
                {
                // new client
                sockaddr_in client;
                socklen_t addr_size = sizeof(sockaddr_in);
                int client_sock = accept(m_serverSocket, (sockaddr *)&client, &addr_size); 
                if (client_sock == -1)
                {
                    perror("accept failed");
                    continue;
                }
                    //add to pool set
                    add_client(client_sock);
                
                }
                else
                {
                    //OnMessage should get called
                    onMessage(it->fd);
                }
            }
            else if (it->revents & POLLERR)
            {
                if (it->fd == m_serverSocket)
                {
                    // listen socket error
                    perror("listen socket error");
                    exit(1);
                }
                else
                {
                // client error
                    del_client(it);
                }
            }
        }
    }
}

void server::set_reuse_addr(int listen_sock)
{
    int ret;
    if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(ret)) == -1) 
    {
        perror("set_reuse_addr error");
        exit(1);
    }
}


void server::onMessage(int clientSocket)
{
    Data data;
    int read_size  = read(clientSocket, &data, sizeof(Data));
    //int read_size = recv(it->fd, message, BUF_SIZE, 0);
    if (read_size <= 0) 
    {        
        // client close
        //del_client(clientSocket);
    }
    else
    {        
        // receive data
        //print_recv(it->fd, message);
        if(read_size== sizeof(Data) )
        {
            std::cout << "From client " << clientSocket << " ";
            std::cout<<"i : " << data.i <<" j: " << data.j<<std::endl;
        }
                        
        //Send the message back to client
        //send(it->fd, message, strlen(message)+1, 0);
        //print_send(it->fd, message);
    }
}
void server::onConnect()
{

}
void server::onDisconnect()
{

}