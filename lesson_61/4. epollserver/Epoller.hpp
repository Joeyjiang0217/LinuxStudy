#ifndef D97876D4_8331_4A2B_9DDA_23A2867B6F07
#define D97876D4_8331_4A2B_9DDA_23A2867B6F07

#include "nocopy.hpp"
#include "Log.hpp"
#include <sys/epoll.h>
#include <cstring>


class Epoller : public NoCopy
{
    static const int size = 128;
public:
    Epoller()
    {
        _epollfd = epoll_create(size);
        if (_epollfd < 0)
        {
            lg(Error, "epoll_create error, %s: %d", strerror(errno), errno);
            exit(-1);
        }
        else
        {
            lg(Info, "epoll_create success, epollfd: %d", _epollfd);
        }
    }

    int EpollerWait(struct epoll_event revents[], int num)
    {
        int n = epoll_wait(_epollfd, revents, num, _timeout);
        return n;
    }

    int EpollerUpdate(int oper, int sock, uint32_t event)
    {
        int n = 0;
        if (oper == EPOLL_CTL_DEL)
        {
            n = epoll_ctl(_epollfd, oper, sock, nullptr);
            if (n != 0)
            {
                lg(Error, "epoll_ctl del error, %s: %d", strerror(errno), errno);
            }
            else
            {
                lg(Info, "epoll_ctl del success, sock: %d", sock);
            }
        }
        else
        {
            // EPOLL_CTL_ADD or EPOLL_CTL_MOD
            struct epoll_event ev;
            memset(&ev, 0, sizeof(ev));
            ev.events = event;
            ev.data.fd = sock;
            n = epoll_ctl(_epollfd, oper, sock, &ev);
            if (n != 0)
            {
                lg(Error, "epoll_ctl mod error, %s: %d", strerror(errno), errno);
            }
        }
        return n;
    }

    ~Epoller()
    {
        if (_epollfd >= 0)
        {
            close(_epollfd);
            lg(Info, "close epollfd: %d", _epollfd);
            _epollfd = -1;
        }
    }
private:
    int _epollfd;
    int _timeout = -1;
};

#endif /* D97876D4_8331_4A2B_9DDA_23A2867B6F07 */
