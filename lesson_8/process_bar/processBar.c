#include "processBar.h"
#include <string.h>

const char* label = "|/-\\";


char bar[NUM] = {0};


void processbar(int rate)
{
    if (rate < 0 || rate > 100)
    {
        return;
    }
    int len = strlen(label);

    printf(GREEN"[%-100s][%d%%][%c]\r"NONE, bar, rate, label[rate % len]);
    fflush(stdout);
    bar[rate++] = BODY;
    if (rate < TOP)
    {
        bar[rate] = RIGHT; 
    }

        //int tmp = cnt;
        //while(tmp != 0)
        //{
            //printf("#");
            //tmp--;
        //}
        //fflush(stdout);
        //printf("\r");
        //cnt++;
        //sleep(1);
}


void init_bar()
{
    memset(bar, '\0', sizeof(bar));
}

