#include "UdpServer.hpp"
#include <memory>

void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " port[1024+]\n" << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(0);
    }

    uint16_t port = std::stoi(argv[1]);

    // 0-1023 系统内定的端口号，一般都要有固定的应用层协议使用， http: 80 https: 443 mysql: 3306...
    std::unique_ptr<UdpServer> svr(new UdpServer(port));

    svr->Init();
    svr->Run();

    return 0;
}