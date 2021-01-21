/*H*************************************************************************
* Description:
*   demo of creating a isolated process
* Function:
*   main()           - clone a process in new UTS, PID, mount namespace
*   container_main() - add itself to control group "mygroup" which sets limits in cpu and memory
*                    - change root directory and open a shell
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
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char* const container_args_chroot[] = {
    "/usr/sbin/chroot",
    "alpine",
    "sh",
    NULL
};

int container_main(void *arg)
{
    printf("Container [%5d] - inside the container!\n", getpid());
    system("mount -t proc proc alpine/proc");
    system("echo 1 > /sys/fs/cgroup/cpu/mygroup/tasks");
    system("echo 1 > /sys/fs/cgroup/memory/mygroup/tasks");
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