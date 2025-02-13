#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.hpp"

Log log;

enum
{
    SOCKET_ERR=1,
    BIND_ERR
};

uint16_t defaultport = 8080;
std::string defaultip = "0.0.0.0";
const int size = 1024;

class UdpServer
{
public:
    UdpServer(const uint16_t& port = defaultport, 
        const std::string& ip = defaultip)
        : sockfd_(0), port_(port), ip_(ip), isrunning_(false)
    {
    }

    void Init()
    {
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ < 0)
        {
            log(Fatal, "socket create error, sockfd: %d", sockfd_);
            exit(SOCKET_ERR);
        }
        log(Info, "socket create successed, sockfd: %d", sockfd_);
        
        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port_);
        // local.sin_addr.s_addr = inet_addr(ip_.c_str());
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        int n = bind(sockfd_, (const struct sockaddr*)&local, sizeof(local));
        if (n < 0)
        {
            log(Fatal, "bind error, errno: %d, err string: %s", errno, strerror(errno));
            exit(BIND_ERR);
        }
        log(Info, "bind successed, errno: %d, err string: %s", errno, strerror(errno));
    }

    void Run()
    {
        isrunning_ = true;
        char inbuffer[size];
        while(isrunning_)
        {
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            ssize_t n = recvfrom(sockfd_, inbuffer, sizeof(inbuffer) - 1, 0, (struct sockaddr*)&client, &len);
            if (n < 0)
            {
                log(Warning, "recvfrom error, errno: %d, err string: %s", errno, strerror(errno));
                continue;
            }
            inbuffer[n] = 0;

            std::string info = inbuffer;
            std::string echo_string = "server echo#" + info;

            std::cout << echo_string << std::endl;

            sendto(sockfd_, echo_string.c_str(), echo_string.size(), 0, (const struct sockaddr*)&client, len);
        }
    }

    ~UdpServer()
    {
        if (sockfd_>0)
        {
            close(sockfd_);
        }
    }

private:
    int sockfd_;
    std::string ip_;
    uint16_t port_;
    bool isrunning_;
};