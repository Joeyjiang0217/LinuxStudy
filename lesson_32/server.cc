#include "comm.hpp"
#include "log.hpp"

using namespace std;

// manage the pipe file
int main()
{
    //logmessage(Info, "hello %s * %d", "world", 10);

    // cout << sum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
    // cout << sum(1, 1) << endl;
    // cout << sum(3, 1, 2, 3) << endl;

    // create a tunnel
    Init init;
    Log log;
    log.Enable(Onefile);

    //open a tunnel
    int fd = open(FIFO_FILE, O_RDONLY);
    if(fd < 0)
    {
        //perror("open: ");
        
        exit(FIFO_OPEN_ERR);
    }

    //cout << "server open file done" << endl;
    log(Info, "Server opened file. Error string: %s, error code: %d", strerror(errno), errno);
    log(Warning, "Server opened file. Error string: %s, error code: %d", strerror(errno), errno);
    log(Fatal, "Server opened file. Error string: %s, error code: %d", strerror(errno), errno);
    log(Debug, "Server opened file. Error string: %s, error code: %d", strerror(errno), errno);

    // start communication
    while(true)
    {
        char buffer[1024] = {0};
        int x = read(fd, buffer, sizeof(buffer));
        if(x > 0)
        {
            buffer[x] = 0;
            cout << "client says# " << buffer << endl;
        }
        else if(x == 0)
        {
            //cout << "client quit, me too!\n" << endl;
            log(Debug, "Client quit, me too! Error string: %s, error code: %d", strerror(errno), errno);
            break;
        }
        else
        {
            break;
        }
    }


    close(fd);

    

    return 0;
}