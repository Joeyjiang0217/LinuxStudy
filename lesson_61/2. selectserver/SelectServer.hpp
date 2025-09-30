#ifndef DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7
#define DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7

#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include "Socket.hpp"

using namespace std;

static const uint16_t DEFAULT_PORT = 8081;
static const int fd_num_max = (sizeof(fd_set) * 8);
int default_fd = -1;

class SelectServer
{
public:
    SelectServer(uint16_t port = DEFAULT_PORT)
        : _port(port)
    {
        for (int i = 0; i < fd_num_max; ++i)
        {
            fd_array[i] = default_fd;
        }
    }
    ~SelectServer()
    {
        _listensock.Close();
    }

    bool Init()
    {
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();
        std::cout << "Server initialized and listening on port " << _port << "." << std::endl;
        return true;
    }

    void Accepter()
    {
        std::string clientip;
        uint16_t clientport = 0;
        int sock = _listensock.Accept(&clientip, &clientport);
        if (sock < 0)
        {
            return; 
        }
        lg(Info, "accept a new client, ip: %s, port: %d", clientip.c_str(), clientport);

        int pos = 1;
        for (; pos < fd_num_max; ++pos)
        {
            if (fd_array[pos] != default_fd)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        if (pos == fd_num_max)
        {
            lg(Warning, "max client num reached");
            close(sock);
            return;
        }
        else
        {
            fd_array[pos] = sock;
            PrintFd();
        }
    }

    void Receiver(int fd, int i)
    {
        char buffer[1024];
        ssize_t bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0)
        {
            lg(Warning, "recv error, fd: %d, %s: %d", fd, strerror(errno), errno);
            close(fd);
            fd_array[i] = default_fd;
        }
        else if (bytes_received == 0)
        {
            lg(Info, "client disconnected, fd: %d", fd);
            close(fd);
            fd_array[i] = default_fd;
        }
        else
        {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            std::cout << "Received data: " << buffer << std::endl;
            // Echo the data back to the client
        }
    }

    void Dispatcher(fd_set& read_fds)
    {
        for (int i = 0; i < fd_num_max; i++)
        {
            int fd = fd_array[i];
            if (fd == default_fd)
            {
                continue;
            }

            if (FD_ISSET(fd, &read_fds))
            {
                if (fd == _listensock.Fd())
                {
                    Accepter();
                }
                else
                {
                    Receiver(fd, i);
                }
            }
        }
    }



    void Start()
    {
        int listensockfd = _listensock.Fd();


        fd_array[0] = listensockfd;
        struct timeval timeout = {1, 0}; // 5 seconds timeout
        for (;;)
        {
            fd_set read_fds;
            FD_ZERO(&read_fds);
            int maxfd = fd_array[0];
            for (int i = 0; i < fd_num_max; ++i)
            {
                if (fd_array[i] == default_fd)
                {
                    continue;
                }
                FD_SET(fd_array[i], &read_fds);
                if (fd_array[i] > maxfd)
                {
                    maxfd = fd_array[i];
                    lg(Info, "maxfd: %d", maxfd);
                }
            }

            timeout.tv_sec = 0; // Reset timeout for each select call
            timeout.tv_usec = 0;
            // int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
            int n = select(maxfd + 1, &read_fds, nullptr, nullptr, nullptr);
            switch (n)
            {
            case -1:
                std::cerr << "Error occurred in select." << std::endl;
                break;
            case 0:
                std::cout << "Timeout occurred, no data available." << 
                timeout.tv_sec << " seconds." << 
                timeout.tv_usec << " microseconds." << std::endl;
                break;
            default:
                // TODO
                // cout << "New connection request received." << endl;
                Dispatcher(read_fds);
                break;
            }
        }

    }

    void PrintFd()
    {
        std::cout << "Current active fds: ";
        for (int i = 0; i < fd_num_max; ++i)
        {
            if (fd_array[i] != default_fd)
            {
                std::cout << fd_array[i] << " ";
            }
        }
        std::cout << std::endl;
    }
private:
    Sock _listensock;
    uint16_t _port;
    int fd_array[fd_num_max];
};


#endif /* DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7 */
