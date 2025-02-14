#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

using namespace std;

void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " port[1024+]\n" << std::endl;
}

struct ThreadData
{
    struct sockaddr_in server;
    int sockfd;
};


void* recv_message(void* args)
{
    ThreadData* td = static_cast<ThreadData*>(args);
    char buffer[1024];
    while(true)
    {
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);

        size_t s = recvfrom(td->sockfd, buffer, 1023, 0, (struct sockaddr*)&temp, &len);
        if (s > 0)
        {
            buffer[s] = 0;
            cout << buffer << endl;
        }
    }
}

void* send_message(void* args)
{
    ThreadData* td = static_cast<ThreadData*>(args);
    string message;
    socklen_t len = sizeof(td->server);
    while(true)
    {

        cout << "Please Enter@ ";
        getline(cin, message);

        // std::cout << message << std::endl;
        // 1. 数据 2. 给谁发
        sendto(td->sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&(td->server), len);
    }
}

// ./udpclient serverip serverport
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    struct ThreadData td;

    bzero(&td.server, sizeof(td.server));
    td.server.sin_family = AF_INET;
    td.server.sin_port = htons(serverport);
    td.server.sin_addr.s_addr = inet_addr(serverip.c_str());


    td.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (td.sockfd < 0)
    {
        cout << "socket error" << endl;
        return 1;
    }

    pthread_t recvr, sender;
    pthread_create(&recvr, nullptr, recv_message, &(td));
    pthread_create(&sender, nullptr, send_message, &(td));



    pthread_join(recvr, nullptr);
    pthread_join(sender, nullptr);

    close(td.sockfd);
    return 0;
}