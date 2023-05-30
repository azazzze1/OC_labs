#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void handle_signal(int sig, siginfo_t *info, void* context){
    printf("Отправлен сигнал %d со значением %d\n", sig, info->si_value.sival_int);        
}


int main(){
    struct sigaction act; 
    union sigval value;
    
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    
    for(int i = SIGRTMIN; i <= SIGRTMAX; ++i){
        sigaddset(&act.sa_mask, i); 
    }

    for(int i = 1; i <= 4; ++i){
        sigaction(SIGINT + i, &act, NULL);
        sigaction(SIGRTMIN + i, &act, NULL); 
    }

    /* 4 - количество сигналов */
    for(int i = 1; i <= 4; ++i){
        value.sival_int = i;
        printf("Отправляем сигнал %d со значением %d\n", SIGINT + i, value.sival_int); 
        
        if(sigqueue(getpid(), SIGINT + i, value) != 0){
            perror("sigqueue");
            exit(EXIT_FAILURE); 
        }
        printf("Отправляем сигнал %d со значением %d\n", SIGRTMIN + i, value.sival_int);

        if(sigqueue(getpid(), SIGRTMIN + i, value) != 0){
            perror("sigqueue");
            exit(EXIT_FAILURE); 
        }
    }

    sleep(1);

    return 0;
}
