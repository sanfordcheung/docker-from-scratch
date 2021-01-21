/*H*************************************************************************
* Description:
*   demo of creating a isolated process
*
* Function:
*   main()           - clone a process in new UTS, PID, mount namespace
*   container_main() - add itself to control group "mygroup" which sets limits in cpu and memory
*                    - change root directory and open a shell
*   create_mygroup() - create cgroup and set limits
*   limit_resources()- add container process to mygroup
*
* Notes:
*   The shell process has a pid 1 and runs in alpine/ directory as its root directory.
*   This process has cpu and memory usage limit, controlled by cgroup.
*   This process has is own UTS, PID, mount namespace. Changing the hostname won't take effect on the host.
*   Besides, it cannot see other processes running on the host.
* 
*H*/

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

#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char* const container_args_chroot[] = {
    "/usr/sbin/chroot",
    "alpine",
    "sh",
    NULL
};

void create_mygroup()
{
    mkdir("/sys/fs/cgroup/cpu/mygroup", S_IRUSR | S_IWUSR);
    FILE *fp = fopen("/sys/fs/cgroup/cpu/mygroup/cpu.cfs_quota_us", "a");
    if (fp == NULL)
      exit(1);
    fputs("40000", fp);
    fclose(fp);

    mkdir("/sys/fs/cgroup/memory/mygroup", S_IRUSR | S_IWUSR);
    fp = fopen("/sys/fs/cgroup/memory/mygroup/memory.limit_in_bytes", "a");
    if (fp == NULL)
      exit(1);
    fputs("655360", fp);
    fclose(fp);
}

void limit_resources()
{
    FILE *fp = fopen("/sys/fs/cgroup/cpu/mygroup/tasks", "a");
    fputs("1", fp);
    fclose(fp);
  
    fp = fopen("/sys/fs/cgroup/memory/mygroup/tasks", "a");
    fputs("1", fp);
    fclose(fp);
}

int container_main(void *arg)
{
    printf("Container [%5d] - inside the container!\n", getpid());
    create_mygroup();
    limit_resources();
    mount("proc", "alpine/proc", "proc", 0, 0);

    execv(container_args_chroot[0], container_args_chroot); 
    printf("Something's wrong!\n");
    return 0;
}

int main()
{
    printf("Parent [%5d] - start a container!\n", getpid());

    int container_pid = clone(container_main, container_stack+STACK_SIZE, CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);

    waitpid(container_pid, NULL, 0);
    printf("Parent - container stopped!\n");
    return 0;
}