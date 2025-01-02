#include "comm.hpp"

extern Log log;

int main()
{
    int shmid = CreateShm();
    char* shmaddr = (char*)shmat(shmid, nullptr, 0);

    // ipc code

    Init init;
    int fd = open(FIFO_FILE, O_RDONLY);
    if(fd < 0)
    {
        //perror("open: ");
        
        exit(FIFO_OPEN_ERR);
    }

    sleep(3);

    struct shmid_ds shmds;
    while(true)
    {   
        char c;
        ssize_t s = read(fd, &c, 1);
        if(s == 0)
        {
            break;
        }
        else if(s < 0)
        {
            break;
        }

        cout << "client says@ " << shmaddr;

        shmctl(shmid, IPC_STAT, &shmds);

        cout << "shm size: " << shmds.shm_segsz << endl;
        cout << "shm nattach: " << shmds.shm_nattch << endl;
        printf("shm __key: 0x%x\n" ,shmds.shm_perm.__key);
        cout << "shm mode: " << shmds.shm_perm.mode << endl;

    }

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, nullptr);

    close(fd);
    return 0;
}


// int main()
// {
//     sleep(2);

//     int shmid = CreateShm();
//     log(Debug, "create shm done");
//     sleep(2);


//     char* shmaddr = (char*)shmat(shmid, nullptr, 0);
//     log(Debug, "attach shm done, shmaddr: 0x%x", shmaddr);
//     sleep(2);

//     shmdt(shmaddr);
//     log(Debug, "detach shm done, shmaddr: 0x%x", shmaddr);
//     sleep(2);

//     shmctl(shmid, IPC_RMID, nullptr);
//     log(Debug, "destroy shm done, shmaddr: 0x%x", shmaddr);
//     sleep(2);

//     return 0;
// }

