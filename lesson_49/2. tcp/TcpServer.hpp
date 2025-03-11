#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <pthread.h>
#include "log.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include "Daemon.hpp"

const int defaultfd = -1;
const std::string defaultip = "0.0.0.0";
const int backlog = 5;

extern Log lg;

enum
{
    UsageError = 1,
    SockError,
    BindError,
    ListenError
};

class TcpServer;

class ThreadData
{
public:
    ThreadData(int fd, const std::string& ip, const uint16_t& p, TcpServer* t)
        : sockfd(fd), clientip(ip), clientport(p), tsvr(t )
    {

    }

public:
    int sockfd;
    std::string clientip;
    uint16_t clientport;
    TcpServer* tsvr;
};

class TcpServer
{
public:
    TcpServer(const uint16_t& port, const std::string& ip = defaultip)
        :listensockfd_(defaultfd), port_(port), ip_(ip)
    {

    }

    void InitServer()
    {
        listensockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (listensockfd_ <0)
        {
            lg(Fatal, "create socket, errno: %d, errstring: %s", errno, strerror(errno));
            exit(SockError);
        }
        lg(Info, "create socket success, listensockfd: %d", listensockfd_);

        int opt;
        setsockopt(listensockfd_, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt));
        struct sockaddr_in local;
        memset(&local, 0, sizeof(sockaddr_in));

        local.sin_family = AF_INET;
        local.sin_port = htons(port_);
        inet_aton(ip_.c_str(), &(local.sin_addr));
        // local.sin_addr.s_addr = INADDR_ANY:

        if(bind(listensockfd_, (const struct sockaddr*)&local, sizeof(local)) < 0)
        {
            lg(Fatal, "bind error, errno: %d, errstring: %s", errno, strerror(errno));
            exit(BindError);
        }

        lg(Info, "bind socket success, listensockfd: %d", listensockfd_);

        if (listen(listensockfd_, backlog) < 0)
        {
            lg(Fatal, "listen error, errno: %d, errstring: %s", errno, strerror(errno));
            exit(ListenError);
        }

        lg(Info, "listen socket success, listensockfd: %d", listensockfd_);
    }

    // static void* Routine(void* args)
    // {
    //     pthread_detach(pthread_self());
    //     ThreadData* td = static_cast<ThreadData*>(args);
    //     td->tsvr->Service(td->sockfd, td->clientip, td->clientport);
    //     delete td;
    //     return nullptr;
    // }

    void Start()
    {
        Daemon();
        ThreadPool<Task>::GetInstance()->Start();
        // signal(SIGCHLD, SIG_IGN);
        lg(Info, "tcpServer is running....");
        for ( ; ; )
        {
            // 1. 获取新连接
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            int sockfd = accept(listensockfd_, (struct sockaddr*)&client, &len);
            if (sockfd < 0)
            {
                lg(Warning, "accept error, errno: %d, errstring: %s", errno, strerror(errno));
                continue;
            }
            uint16_t clientport = ntohs(client.sin_port);
            char clientip[32];  
            inet_ntop(AF_INET, &(client.sin_addr), clientip, sizeof(clientip));

            // 2. 根据新连接来进行通信
            lg(Info, "get a new link..., sockfd: %d, client ip: %s, client port: %d", sockfd, clientip, clientport);

            // version 1 -- 单进程版
            // Service(sockfd, clientip, clientport);
            // close(sockfd);

            // version 2 -- 多进程版
            // pid_t id = fork();
            // if (id == 0)
            // {
            //     // child
            //     close(listensockfd_);
            //     if (fork() > 0)
            //     {
            //         exit(0);
            //     }
            //     Service(sockfd, clientip, clientport); // 孙子进程， system领养
            //     close(sockfd);
            //     exit(0);
            // }

            // // parent
            // close(sockfd);
            // pid_t rid = waitpid(id, nullptr, 0);
            // (void)rid;

            // version 3 -- 多线程版本
            // ThreadData* td = new ThreadData(sockfd, clientip, clientport, this);
            // pthread_t tid;
            // pthread_create(&tid, nullptr, Routine, td);

            // version 4 --- 线程池版本
            Task t(sockfd, clientip, clientport); 
            ThreadPool<Task>::GetInstance()->Push(t);
        }
    }

    // void Service(int sockfd, const std::string& clientip, const uint16_t& clientport)
    // {
    //     // test
    //     char buffer[4096];
    //     while (true)
    //     {
    //         ssize_t n = read(sockfd, buffer, sizeof(buffer));
    //         if (n > 0)
    //         {
    //             buffer[n] = 0;
    //             std::cout << "client say# " << buffer << std::endl;
    //             std::string echo_string = "tcpserver echo# ";
    //             echo_string += buffer;

    //             write(sockfd, echo_string.c_str(), echo_string.size());
    //         }
    //         else if (n == 0)
    //         {
    //             lg(Info, "%s:%d quit, server close sockfd: %d", clientip.c_str(), clientport, sockfd);
    //             break;
    //         }
    //         else
    //         {
    //             lg(Warning, "read error, sockfd: %d, client ip: %s, client port: %d", sockfd, clientip.c_str(), clientport);
    //             break;
    //         }
    //     }
    // }

    ~TcpServer()
    {

    }
private:
    int listensockfd_;
    uint16_t port_;
    std::string ip_;

};