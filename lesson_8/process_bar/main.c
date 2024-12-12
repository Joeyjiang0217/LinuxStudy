#include "processBar.h"
#include <unistd.h>

typedef void (*call_back_t)(int);

void download(call_back_t cb)
{
    int total = 1000;
    int cur = 0;
    init_bar();
    while (cur <= total)
    {
        int rate = (int)(cur * 100.00 / total);
        cb(rate);
        usleep(1000);
        cur++;
    }
    printf("\n");
}


int main()
{
    printf("download_1:\n");
    download(processbar);
    printf("download_2:\n");
    download(processbar);
    printf("download_3:\n");
    download(processbar);
    printf("download_4:\n");
    download(processbar);

    //int cnt = 10;
    //while(cnt)
    //{
        //printf("%02d\r", cnt);
        //cnt--;
        //fflush(stdout);
        //sleep(1);
    //}
    //printf("%02d", 0);
    //printf("\n");


    //#printf("hello world");
    //#fflush(stdout);
    //#sleep(2);
    //#printf("hello world");
    return 0;
}
