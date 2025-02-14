#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
#include <unordered_map>
#include "log.hpp"

// using func_t = std::function<std::string(const std::string&)>;
typedef std::function<std::string(const std::string &i, const std::string&, uint16_t)> func_t;

Log lg;

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
            lg(Fatal, "socket create error, sockfd: %d", sockfd_);
            exit(SOCKET_ERR);
        }
        lg(Info, "socket create successed, sockfd: %d", sockfd_);
        
        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port_);
        // local.sin_addr.s_addr = inet_addr(ip_.c_str());
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        int n = bind(sockfd_, (const struct sockaddr*)&local, sizeof(local));
        if (n < 0)
        {
            lg(Fatal, "bind error, errno: %d, err string: %s", errno, strerror(errno));
            exit(BIND_ERR);
        }
        lg(Info, "bind successed, errno: %d, err string: %s", errno, strerror(errno));
    }

    void CheckUser(const struct sockaddr_in& client, const std::string clientip, uint16_t clientport)
    {
        auto iter = onlineuser.find(clientip);
        if (iter == onlineuser.end())
        {
            onlineuser.insert({clientip, client});
             std::cout << "[" << clientip << ":" << clientport << "] was added to the online user map." << std::endl; 

        }
        else
        {

        }
    }

    void Broadcast(const std::string info, const std::string clientip, uint16_t clientport)
    {
        for(const auto& user : onlineuser)
        {
            std::string message = "[";
            message += clientip;
            message += ":";
            message += std::to_string(clientport);
            message += "]#";
            message += info;
            socklen_t len = sizeof(user.second);
            sendto(sockfd_, message.c_str(), message.size(), 0, (const struct sockaddr*)(&user.second), len);
        }
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
                lg(Warning, "recvfrom error, errno: %d, err string: %s", errno, strerror(errno));
                continue;
            }
            uint16_t clientport = ntohs(client.sin_port);
            std::string clientip = inet_ntoa(client.sin_addr);
            CheckUser(client, clientip, clientport);
            std::string info = inbuffer;
            Broadcast(info, clientip, clientport);

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
    std::unordered_map<std::string, struct sockaddr_in> onlineuser;
};