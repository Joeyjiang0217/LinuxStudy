#include "UdpServer.hpp"
#include <memory>
#include <cstdio>
#include <vector>

void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " port[1024+]\n" << std::endl;
}

// std::string Hander(const std::string &info, const std::string& clientip, uint16_t clientport)
// {
//     std::cout << "[" << clientip << ":" << clientport << "]# " << info << std::endl; 
//     std::string res = "Server gets a message: ";
//     res += info;
//     std::cout << res << std::endl;

//     // pid_t id = fork();
//     // if (id == 0)
//     // {

//     // }

//     return res;
// }

// bool SafeCheck(const std::string& cmd)
// {
//     int safe = false;
//     std::vector<std::string> key_word = {
//         "rm",
//         "mv",
//         "cp",
//         "kill",
//         "sudo",
//         "unlink",
//         "uninstall",
//         "apt",
//         "top",
//         "while"
//     };

//     for (auto& word : key_word)
//     {
//         auto pos = cmd.find(word);
//         if (pos != std::string::npos)
//         {
//             return false;
//         }
//     }
//     return true;

// }

// std::string ExcuteCommand(const std::string& cmd)
// {
//     std::cout << "get a request cmd: " << cmd << std::endl;
//     if (!SafeCheck(cmd))
//     {
//         return "Bad man";
//     }
//     FILE* fp = popen(cmd.c_str(), "r");
//     if (fp == NULL)
//     {
//         perror("popen");
//         return "error";
//     }

//     std::string res;
//     char buffer[4096];
//     while(true)
//     {
//         char* ok = fgets(buffer, sizeof(buffer), fp);
//         if (ok == nullptr)
//         {
//             break;
//         }
//         res += buffer; 
//     }

//     pclose(fp);
//     return res;
// }

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