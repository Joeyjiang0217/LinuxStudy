#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void Usage(const std::string& proc)
{
    std::cout << "\n\rUsage: " << proc << " serverip serverport\n" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }

    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport);
    inet_pton(AF_INET, serverip.c_str(), &(server.sin_addr));


    while (true)
    {
        int cnt = 5;
        int isreconnect = false;
        int sockfd = 0;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            std::cerr << "socket error" << std::endl;
            return 1;
        }
        do
        {


            // tcp客户端要不要bind？要不要显式的bind？系统进行bind，随机端口
            // 客户端发起connect的时候，进行自动随机bind
            int n = connect(sockfd, (const struct sockaddr *)&server, sizeof(server));
            if (n < 0)
            {
                isreconnect = true;
                cnt--;
                std::cerr << "connect error..., reconnect: " << cnt << std::endl;
                // close(sockfd);
                sleep(2);
            }
            else
            {
                break;
            }
        } while (cnt && isreconnect);

        if (cnt == 0)
        {
            std::cerr << "user offline..." << std::endl;
            break;
        }

        std::string message;

        std::cout << "Please Enter# ";
        std::getline(std::cin, message);

        int n = write(sockfd, message.c_str(), message.size());
        if (n < 0)
        {
            isreconnect = true;
            std::cerr << "write error..." << std::endl;
            // continue;
        }

        char inbuffer[4096];
        n = read(sockfd, inbuffer, sizeof(inbuffer));

        if (n > 0)
        {
            inbuffer[n] = 0;
            std::cout << inbuffer << std::endl;
        }
        close(sockfd);
    }


    return 0;
}