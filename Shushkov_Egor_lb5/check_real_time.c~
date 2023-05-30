#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void handle_real_time_signal(int sig, siginfo_t *info, void* context){
    printf("Обрабатывается сигнал реального времени %d", sig);
    usleep(1000000);     
}

void handle_normal_signal(int sig){
    printf("Обрабатывается обычный сигнал %d\n", sig); 
}


int main(){
    freopen("log.txt", "w", stdout); 

    struct sigaction act; 
    union sigval value;
    
    act.sa_sigaction = handle_real_time_signal;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    
    for(int i = SIGRTMIN; i <= SIGRTMAX; ++i){
        sigaction(i, &act, NULL);
    }

    for(int i = 1; i <= 5; ++i){
        signal(i, handle_normal_signal); 
    }

    printf("Отправляем сигнал\n"); 

    /* 5 - количество сигналов */
    for(int i = 1; i <= 5; ++i){
        printf("Отправляем нормальный сигнал %d\n", i); 
        kill(getpid(), i);    
    }
    for(int i = SIGRTMIN; i <= SIGRTMAX; ++i){
        printf("Отправляем сигнал реального времени %d\n", i); 
        kill(getpid(), i); 
    }

    printf("Сигналы отправлены. Обработка...\n");

    sleep(5);

    return 0;
}
