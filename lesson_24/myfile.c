#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    //printf("hello Linux");
    //close(1);
    const char* fstr = "hello fwrite\n";
    const char* str = "hello write\n";
  

    printf("hello printf\n");
    sleep(2);
    fprintf(stdout, "hello fprintf\n");
    sleep(2);
    fwrite(fstr, strlen(fstr), 1, stdout);
    sleep(2);
  
    write(1, str, strlen(str));
    sleep(5);
    //close(1);
    fork();
    return 0;
}
