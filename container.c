#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define STACK_SIZE (1024*1024)
static char container_stack[STACK_SIZE];

char *const container_args[] = {
    "/bin/bash",
    NULL
};


void create_mygroup()
{
    mkdir("/sys/fs/cgroup/cpu/mygroup", S_IRUSR | S_IWUSR);
    FILE *fp = fopen("/sys/fs/cgroup/cpu/mygroup/cpu.cfs_quota_us", "a");
    if(fp)
    {
        fputs("40000", fp);
        fclose(fp);
    }
    mkdir("/sys/fs/cgroup/memory/mygroup", S_IRUSR | S_IWUSR);
    fp = fopen("/sys/fs/cgroup/memory/mygroup/memory.limit_in_bytes", "a");
    if(fp)
    {
        fputs("3000000", fp);
        fclose(fp);
    }
}

void limit_resource()
{
    FILE *fp = fopen("/sys/fs/cgroup/cpu/mygroup/tasks", "a");
    if(fp)
    {
        fputs("1", fp);
        fclose(fp);
    }
    fp = fopen("/sys/fs/cgroup/memory/mygroup/tasks", "a");
    if(fp)
    {
        fputs("1", fp);
        fclose(fp);
    }
}

void remove_mygroup()
{
    rmdir("/sys/fs/cgroup/cpu/mygroup");
    rmdir("/sys/fs/cgroup/memory/mygroup");
}

int container_main(void *args)
{
    printf("\n [%5d] inside container\n", getpid());
    sethostname("container", 10);
    limit_resource();
    mount("proc", "/proc", "proc", 0, 0);
    execv(container_args[0], container_args);
    return 0;
}

int main()
{
    printf("\n [%5d] main\n", getpid());
    create_mygroup();
    int child = clone(container_main, container_stack+STACK_SIZE, CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, NULL);
    waitpid(child, NULL, 0);
    remove_mygroup();
    printf("\n container stopped\n");
    return 0;
}