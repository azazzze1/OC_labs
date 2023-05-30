#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(){
    int child_pid = getpid(); 
    int ppid = getppid();
    printf("Процесс-ребёнок запустился: pid = %d\n", child_pid);
    
    kill(ppid, SIGTRAP); 

    printf("Сигнал SIGTRAP был обработан в процессе-ребёнке\n"); 

    while(1){
        sleep(2);
    }
}

