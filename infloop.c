#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum)
{
    printf("infloop receive signal: %d\n", signum);
    exit(1);
}


int main(void)
{
    signal(SIGINT, sig_handler);
    printf("going to infinite looping\n");
    int i = 0;
    for(;;) i++;
    return 0;
}