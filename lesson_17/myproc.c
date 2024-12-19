#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main()
{
    printf("you can see me!");
    sleep(1);
    _exit(11);
}

//void show()
//{
    //printf("void show()\n");
    //exit(11);
//}
//
//
//int main()
//{
    //printf("hello linux\n");
    //show();
    //exit(12);
//
    ////while(1)
    ////{
        ////printf("hello Linux. pid: %d\n", getpid());
        ////sleep(1);
    ////}
//
//
    ////char *p = NULL;
    ////*p = 0;
    ////return 0;
//
    ////int ret = 0;
    ////char* p = (char*)malloc(1000*1000*1000*4);
    ////if(p == NULL)
    ////{
        ////printf("malloc failed, %d: %s\n", errno, strerror(errno));
        ////ret = errno;
    ////}
    ////else
    ////{
        ////printf("malloc success\n");
    ////}
    ////return errno;
//}


//int main()
//{
    //printf("Simulating a program\n");
    //int i = 0;
    //for(; i < 20; i++)
    //{
        //printf("%d: %s\n", i, strerror(i));
    //}
//
//
    //return 10;
//}




//#define N 5
//
//void runChild()
//{
    //int cnt = 10;
    //while(cnt)
    //{
        //printf("I am a child: %d, ppid: %d\n", getpid(), getppid());
        //sleep(1);
        //cnt--;
    //}
//}
//
//
//int main()
//{   
    //int i = 0;
    //for(; i < N; i++)
    //{
        //pid_t id = fork();
        //if (id == 0)
        //{
            //runChild();
            //exit(0);
        //}
    //}
    //sleep(1000);
//
//
    //int cnt = 5;
    //pid_t id_1 = fork();
    //if (id_1 != 0)
    //{
        //pid_t id_2 = fork();
        //if (id_2 != 0)
        //{
            //pid_t id_3 = fork();
        //}
//
    //}
    //printf("pid: %d, ppid: %d\n", getpid(), getppid());


    //printf("pid: %d before\n", getpid());
//
    //fork();
//
    //printf("pid: %d after\n", getpid());
    //return 0;
//}
