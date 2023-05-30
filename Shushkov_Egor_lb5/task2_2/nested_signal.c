#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void (*user_signal(int sig, void (*hndler)(int))) (int){
    struct sigaction act, prev_act;
    act.sa_handler = hndler; 
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0; 
    
    if(sigaction(sig, &act, 0) < 0){
        return SIG_ERR;
    }
    return act.sa_handler; 
}

void SIGUSR1_handler(int sig){
    if(sig != SIGUSR1){
        printf("Поймане не то сигнал\n");
        return;
    }
    printf("SIGUSR1 пойман. Отсылаем SIGINT\n"); 
    kill(getpid(), SIGINT); 
    sleep(10); 
}

int main(){
    user_signal(SIGUSR1, SIGUSR1_handler); 
    while(1){
        pause(); 
    }
}
