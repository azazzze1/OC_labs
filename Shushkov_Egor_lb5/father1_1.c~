#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void sigsegv_handler(int sig); 

static void sigtrap_handler(int sig){
    signal(SIGTRAP, sigtrap_handler); 
    printf("Сигнал SIGTRAP обработан в родителе\n"); 
}

int main(){
    int child_pid;
    int pid = getpid();
    printf("Процесс-родитель запустился: pid = %d\n", pid);

    signal(SIGCHLD, SIG_DFL);
    signal(SIGTRAP, sigtrap_handler);
    signal(SIGSEGV, sigsegv_handler);

    if((child_pid = fork()) == 0){
        execl("son1_1", "son1_1", NULL);
    }

    while(1){
        sleep(2);
    }
}

static void sigsegv_handler(int sig){
    signal(SIGSEGV, sigsegv_handler);
    printf("Сигнал SIGSEGV получен\n"); 
}
