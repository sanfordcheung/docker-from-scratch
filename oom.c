#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum)
{
    printf("oom receive signal: %d\n", signum);
    exit(1);
}

int main(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGKILL, sig_handler);

    int one_kb = 1024;
    int one_gb = 1024*1024*1024;

    char *p1 = (char *)malloc(one_kb);
    if (p1 == NULL)
    {
        printf("oom\n");
        exit(1);
    }
    memset(p1, 1, 1024);
    printf("[%d] - memory is allocated 1KB \n", getpid());
    
    char *p2 = (char *)malloc(one_gb);
    if (p2 == NULL)
    {
        printf("oom\n");
        exit(1);
    }
    memset(p2, 1, one_gb);
    printf("[%d] - memory is allocated 1GB \n", getpid());

    free(p1);
    free(p2);
    printf("go to inf loop\n");
    int i = 0;
    for(;;) i++;
    return 0;
}