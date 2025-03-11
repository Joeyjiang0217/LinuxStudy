#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <cassert>
#include "Socket.hpp"
#include "Protocol.hpp"

static void Usage(const std::string& proc)
{
    std::cout << "\nUsage: " << proc << "serverip serverport\n\n" << std::endl;
}

// ./clientcal ip port  
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    Sock sockfd;
    sockfd.Socket();
    bool r = sockfd.Connect(serverip, serverport);
    if (!r)
    {
        return 1;
    }

    srand(time(nullptr) ^ getpid());
    int cnt = 1;
    const std::string opers = "+-*/%=-=&^";

    std::string inbuffer_stream;
    while (cnt <= 10)
    {
        std::cout << "===============第" << cnt << "次测试....., " << "==================" << std::endl;
        int x = rand() % 100 + 1;
        usleep(1234);
        int y = rand() % 100;
        usleep(4321);
        char oper = opers[rand()%opers.size()];
        Request req(x, y, oper);
        req.DebugPrint();

        std::string package;
        req.Serialize(&package);

        package = Encode(package);

        write(sockfd.Fd(), package.c_str(), package.size());
        // std::cout << "这是最新的发出去的请求: \n" << n << "/n" << package;
        // n = write(sockfd.Fd(), package.c_str(), package.size());
        // std::cout << "这是最新的发出去的请求: \n" << n << "/n" << package;
        
        // n = write(sockfd.Fd(), package.c_str(), package.size());
        // std::cout << "这是最新的发出去的请求: \n" << n << "/n" << package;

        // n = write(sockfd.Fd(), package.c_str(), package.size());
        // std::cout << "这是最新的发出去的请求: \n" << n << "/n" << package;


        char buffer[120];
        ssize_t n = read(sockfd.Fd(), buffer, sizeof(buffer));

        if (n > 0)
        {
            buffer[0];
            inbuffer_stream += buffer;
            std::cout << inbuffer_stream << std::endl;
            std::string content;
            bool r = Decode(inbuffer_stream, &content);
            assert(r);

            Response resp;
            r = resp.Deserialize(content);
            assert(r);

            resp.DebugPrint();
        }
        
        std::cout << "=================================" << std::endl;
        cnt++;
        sleep(1);
    }

    sockfd.Close();
    return 0;
}