#include "Task.hpp"
#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <sys/wait.h>
#include <sys/stat.h>

const int processnum = 10;

class channel
{
public:
    channel(int cmdfd, int slaverid, const std::string& processname)
    :_cmdfd(cmdfd),
    _slaverid(slaverid),
    _processname(processname)
    {

    }

public:
    int _cmdfd;              // File descriptor for the sending task
    pid_t _slaverid;         // The pid of the child process
    std::string _processname;// The name of the child process
};

void slaver()
{
    while (true)
    {
        //std::cout << getpid() << "read fd is " << rfd << std::endl;
        //sleep(1000);
        int cmdcode = 0;
        int n = read(0, &cmdcode, sizeof(int)); // What if the parent process never sends data to the child process? Blocking wait
        if(n == sizeof(int))
        {
            // execute the list of tasks corresponding to the cmdcode
            std::cout << "slaver says it gets a command: " << getpid() << ": ,cmdcode:" << cmdcode << std::endl;
            if(cmdcode >= 0 && cmdcode < tasks.size())
            {
                tasks[cmdcode]();

            }
            else
            {
                continue;
            }
        }
        if(n == 0)
        {
            break;
        }
    }
    
}

// input: const &
// output: *
// input&output: &
void InitProcessPool(std::vector<channel>* channels)
{
    std::vector<int> oldfds;
    for (int i = 0; i < processnum; i++)
    {
        int pipefd[2]; // tmp space
        int n = pipe(pipefd);
        assert(n==0);
        (void)n;

        
        pid_t id = fork();
        if(id == 0)
        {
            // child
            std::cout << "child: " << getpid() << " close history fd: ";
            for(auto fd : oldfds)
            {
                std::cout << fd << " ";
                close(fd);
            }
            std::cout << "\n";
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            slaver();
            std::cout << "process: " << getpid() << " quit." << std::endl;
            //slaver(pipefd[0]);
            exit(0);
        }
        // parent
        close(pipefd[0]);

        // Add channel field
        std::string name = "process-" + std::to_string(i);
        channels->push_back(channel(pipefd[1], id, name));
        oldfds.push_back(pipefd[1]);
        sleep(1);
    }
    
}

void Debug(const std::vector<channel>& channels)
{
    for(auto &c : channels)
    {
        std::cout << c._cmdfd << " " << c._slaverid << " " << c._processname << std::endl;
    }
}

void Menu()
{
    std::cout << "###########################################################################" << std::endl;
    std::cout << "# 1. Refresh the log          2. Update the jungle                        #" << std::endl;
    std::cout << "# 3. Detect software updates  4. updates the user's blood and mana levels #" << std::endl;
    std::cout << "#                             0. quit                                     #" << std::endl;
    std::cout << "###########################################################################" << std::endl;
}

void ctrlSlaver(const std::vector<channel>& channels)
{
    int which = 0;
    int cnt = 5;
    while(cnt)
    {
        // int select = 0;
        // Menu();
        // std::cout << "Please Enter: ";
        // std::cin >> select;

        // if(select <=0 || select >= 5)
        // {
        //     break;
        // }

        // 1. select a task
        int cmdcode = rand()%tasks.size();
        //int cmdcode = select - 1;

        // 2. select a process
        //int processpos = rand()%channels.size();

        std::cout << "The parent process says that cmdcode, " << cmdcode << ", has already been sent to " << channels[which]._slaverid << ". "
         "process name: " << channels[which]._processname << std::endl;

        // 3. send the task
        write(channels[which]._cmdfd, &cmdcode, sizeof(cmdcode));

        which++;
        which = which % channels.size();
        cnt--;
        sleep(1);
    }
}

void QuitProcess(const std::vector<channel>& channels)
{
    // version 1
    // int last = channels.size() - 1;
    // for(int i = last; i >= 0; i--)
    // {
    //     close(channels[i]._cmdfd);
    //     waitpid(channels[i]._slaverid, nullptr, 0);
    // }

    //version 2


    for(const auto &c : channels)
    {
        close(c._cmdfd);
        waitpid(c._slaverid, nullptr, 0);
    }
    // sleep(3);
    // for(const auto &c : channels)
    // {
    //     waitpid(c._slaverid, nullptr, 0);
    // }
    // sleep(3);
}

int main()
{

    LoadTask(&tasks);
    srand(time(nullptr)^getpid()^1023);

    std::vector<channel> channels;

    // 1. initialization
    InitProcessPool(&channels);
    // test
    Debug(channels);

    // 2. control child processes
    ctrlSlaver(channels);

    // 3. clean
    QuitProcess(channels);

    //sleep(1000);
    return 0;
}