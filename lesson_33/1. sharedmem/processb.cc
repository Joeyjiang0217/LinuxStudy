#include "comm.hpp"


int main()
{
    int shmid = GetShm();
    char* shmaddr = (char*)shmat(shmid, nullptr, 0);

    int fd = open(FIFO_FILE, O_WRONLY);
    if(fd < 0)
    {
        //perror("open: ");
        
        exit(FIFO_OPEN_ERR);
    }

    while(true)
    {
        //char buffer[1024];
        cout << "Please Enter@ ";
        fgets(shmaddr, 4096, stdin);
        //memcpy(shmaddr, buffer, strlen(buffer) + 1);

        write(fd, "c", 1);

    }


    shmdt(shmaddr);

    close(fd);
    return 0;
}