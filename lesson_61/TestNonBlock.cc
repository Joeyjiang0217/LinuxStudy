#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

using namespace std;

void SetNonBlock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        cerr << "Error getting file descriptor flags." << endl;
        return;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        cerr << "Error setting non-blocking mode." << endl;
    }
    else
    {
        cout << "File descriptor set to non-blocking mode." << endl;
    }
}

int main()
{
    char buffer[1024];
    SetNonBlock(0); // Set stdin to non-blocking mode
    // sleep(1);
    while (true)
    {
        // printf("Enter input: ");
        // fflush(stdout);
        ssize_t n = read(0, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = '\0';
            cout << "Read " << n << " bytes: " << buffer;
        }
        else if (n == 0)
        {
            cout << "End of file reached." << endl;
            break;
        }
        else
        {
            if (errno == EAGAIN)
            {
                cout << "No data available right now. Try again later." << endl;
            }
            else
            {
                cerr << "Error reading from stdin." << endl;
                cerr << "Error code: " << errno << " (" << strerror(errno) << ")" << endl;
            }
            
            // break;
            sleep(1);
        }
    }
    return 0;
}
