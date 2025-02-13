#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " port[1024+]\n" << std::endl;
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

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport);
    server.sin_addr.s_addr = inet_addr(serverip.c_str());
    socklen_t len = sizeof(server);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cout << "socket error" << endl;
        return 1;
    }

    string message;
    char buffer[1024];
    while(true)
    {
        cout << "Please Enter@ ";
        getline(cin, message);

        std::cout << message << std::endl;
        // 1. 数据 2. 给谁发
        sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&server, len);

        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);

        size_t s = recvfrom(sockfd, buffer, 1023, 0, (struct sockaddr*)&temp, &len);
        if (s > 0)
        {
            buffer[s] = 0;
            cout << buffer << endl;
        }
    }

    close(sockfd);
    return 0;
}