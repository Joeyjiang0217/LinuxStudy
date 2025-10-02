#ifndef D00F0007_9F33_4495_B094_E6C976EC17DD
#define D00F0007_9F33_4495_B094_E6C976EC17DD

#include <iostream>
#include <memory>
#include <sys/epoll.h>
#include <sys/time.h>
#include "Socket.hpp"
#include "Log.hpp"
#include "Epoller.hpp"
#include "nocopy.hpp"

uint32_t EVENT_IN = (EPOLLIN);
uint32_t EVENT_OUT = (EPOLLOUT);

class EpollServer : public NoCopy 
{
    static const int MAXEVENTS = 64; 
public:
    EpollServer(uint16_t port = 8081)
        : _port(port), _listensock(new Sock()), _epoller(new Epoller())
    {
    }
    ~EpollServer()
    {
        _listensock->Close();
    }

    void Init()
    {
        _listensock->Socket();
        _listensock->Bind(_port);
        _listensock->Listen();
        std::cout << "Server initialized and listening on port " << _port << "." << std::endl;
    }

    void Accepter()
    {
        // New connection
        std::string clientip;
        uint16_t clientport;
        int connfd = _listensock->Accept(&clientip, &clientport);
        if (connfd > 0)
        {
            lg(Info, "Accepted new connection from %s:%d, connfd: %d", clientip.c_str(), clientport, connfd);
            // Add new connection to epoll
            _epoller->EpollerUpdate(EPOLL_CTL_ADD, connfd, EVENT_IN);
        }
    }

    void RecvData(int fd)
    {
        // TODO
        // Data from existing connection
        char buffer[1024] = {0};
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            lg(Debug, "Read %zd bytes from fd %d: %s", n, fd, buffer);
            // Echo back the data
            std::string echo_str = "Echo: ";
            echo_str.append(buffer, n);
            write(fd, echo_str.c_str(), echo_str.size());
        }
        else if (n == 0)
        {
            // Connection closed by client
            lg(Info, "Connection closed by client, fd: %d", fd);
            _epoller->EpollerUpdate(EPOLL_CTL_DEL, fd, 0);
            close(fd);
        }
        else
        {
            lg(Error, "Read error on fd %d, %s: %d", fd, strerror(errno), errno);
            _epoller->EpollerUpdate(EPOLL_CTL_DEL, fd, 0);
            close(fd);
        }
    }

    void Dispatcher(struct epoll_event revents[], int num)
    {
        for (int i = 0; i < num; ++i)
        {
            uint32_t ev = revents[i].events;
            int fd = revents[i].data.fd;
            if (ev & EVENT_IN)
            {
                if (fd == _listensock->Fd())
                {
                    Accepter();
                }
                else
                {
                    RecvData(fd);
                }
            }
            else if (ev & EVENT_OUT)
            {
                // TODO
            }
            else
            {
                // TODO
            }
        }
    }

    void Start()
    {
        // Add the listen socket to epoll -> 
        // Add the listen socket and its associated events to the kernel epoll model's red-blue tree.
        _epoller->EpollerUpdate(EPOLL_CTL_ADD, _listensock->Fd(), EVENT_IN);
        struct epoll_event revs[MAXEVENTS];
        for (;;)
        {
            // TODO
            int n = _epoller->EpollerWait(revs, MAXEVENTS);
            if (n > 0)
            {
                // some events are ready
                lg(Debug, "epoll_wait got %d events", n);
                Dispatcher(revs, n);
            }
            else if (n == 0)
            {
                // timeout, no events
                lg(Info, "epoll_wait timeout");
                continue;
            }
            else
            {
                // error
                lg(Error, "epoll_wait error, %s: %d", strerror(errno), errno);
                continue;
            }
        }
    }
private:
    std::shared_ptr<Sock> _listensock;
    std::shared_ptr<Epoller> _epoller;
    uint16_t _port;


};

#endif /* D00F0007_9F33_4495_B094_E6C976EC17DD */
