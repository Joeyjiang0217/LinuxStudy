#ifndef DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7
#define DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7

#include <iostream>
#include <poll.h>
#include <sys/time.h>
#include "Socket.hpp"

using namespace std;

static const uint16_t DEFAULT_PORT = 8081;
static const int fd_num_max = 64;
int default_fd = -1;
int non_event = 0;

class PollServer
{
public:
    PollServer(uint16_t port = DEFAULT_PORT)
        : _port(port)
    {
        for (int i = 0; i < fd_num_max; ++i)
        {
            _event_fds[i].fd = default_fd;
            _event_fds[i].events = non_event;
            _event_fds[i].revents = non_event;

        }
    }
    ~PollServer()
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
            if (_event_fds[pos].fd != default_fd)
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
            // expand the array
        }
        else
        {
            _event_fds[pos].fd = sock;
            _event_fds[pos].events = POLLIN;
            _event_fds[pos].revents = non_event;
            PrintFd();
        }
    }

    void Receiver(int fd, int i)
    {
        char buffer[1024];
        ssize_t bytes_received = read(fd, buffer, sizeof(buffer) - 1);
        cout << "bytes_received: " << bytes_received << endl;
        if (bytes_received < 0)
        {
            lg(Warning, "recv error, fd: %d, %s: %d", fd, strerror(errno), errno);
            close(fd);
            _event_fds[i].fd = default_fd;
        }
        else if (bytes_received == 0)
        {
            lg(Info, "client disconnected, fd: %d", fd);
            close(fd);
            _event_fds[i].fd = default_fd;
        }
        else
        {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            std::cout << "Received data: " << buffer << std::endl;
            // Echo the data back to the client
        }
    }

    void Dispatcher()
    {
        for (int i = 0; i < fd_num_max; i++)
        {
            int fd = _event_fds[i].fd;
            if (fd == default_fd)
            {
                continue;
            }

            if (_event_fds[i].revents & POLLIN)
            {
                if (fd == _listensock.Fd())
                {
                    Accepter();
                }
                else
                {
                    cout << "Ready to receive data on fd: " << fd << endl;
                    Receiver(fd, i);
                }
            }
        }
    }



    void Start()
    {
        _event_fds[0].fd = _listensock.Fd();
        _event_fds[0].events = POLLIN;
        int timeout = 3000; // 3 seconds

        for (;;)
        {
            int n = poll(_event_fds, fd_num_max, timeout);
            switch (n)
            {
            case -1:
                std::cerr << "Error occurred in select." << std::endl;
                break;
            case 0:
                std::cout << "Timeout occurred, no data available." << std::endl;
                break;
            default:
                // TODO
                // cout << "New connection request received." << endl;
                Dispatcher();
                break;
            }
        }

    }

    void PrintFd()
    {
        std::cout << "Current active fds: ";
        for (int i = 0; i < fd_num_max; ++i)
        {
            if (_event_fds[i].fd != default_fd)
            {
                std::cout << _event_fds[i].fd << " ";
            }
        }
        std::cout << std::endl;
    }
private:
    Sock _listensock;
    uint16_t _port;
    struct pollfd _event_fds[fd_num_max];
    // struct pollfd* _event_fds;
};


#endif /* DC5B04BB_C690_48A2_9E5E_BBEAB2076CB7 */
