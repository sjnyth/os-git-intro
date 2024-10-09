#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define   MAX_COUNT  200

void  ChildProcess(void);       /* child process prototype  */
void  ParentProcess(pid_t process1, pid_t process2);   /* parent process prototype */

void  main(void)
{
    pid_t  pid;
    pid_t pid2;

    pid = fork();
    int i;
    for (i = 0; i < 2; i++) {

    }
    if (pid == 0)
        ChildProcess();
    else
        pid2 = fork();
    if (pid2 == 0)
        ChildProcess();
    else
        ParentProcess(pid, pid2);
}

void  ChildProcess(void)
{
    int i;
    srand(10000);
    int loop_times = rand() % 31; // Generates random number between 0 and 30
    int sleep_time = rand() % 11; // Generates random number between 0 and 10
    for (i = 0; i < loop_times; i++) {
        printf("Child Pid: %ld is going to sleep!\n", (long)getpid());
        sleep(sleep_time);
        printf("Child Pid: %ld is awake!Where is my Parent: %ld\n", (long)getpid(), (long)getppid());
    }
    exit(0);
}

void  ParentProcess(pid_t process1, pid_t process2)
{
    int status1, status2;
    waitpid(process1, &status1, 0);
    printf("Child Pid: %ld has completed\n", (long)process1);
    waitpid(process2, &status2, 0);
    printf("Child Pid: %ld has completed\n", (long)process2);
}
