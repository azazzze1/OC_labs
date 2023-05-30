#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void handler(int sig){
    if(sig == SIGUSR1){
        printf("Получен сигнал SIGUSR1\n");
    }else{ 
        printf("Получен сигнал SIGUSR2\n");
    }

    printf("Родитель = %d\n", getppid());
    signal(sig, SIG_DFL);
}

int main(){
    printf("\nРодитель запустился: pid = %d, ppid = %d\n", getpid(), getppid()); 
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGINT, SIG_DFL);
    signal(SIGCHLD, SIG_IGN);

    int fork_child = fork(); 
    if(fork_child == 0){
        printf("\nПроцесс-ребёнок запустился: pid = %d, ppid = %d\n", getpid(), getppid());

        if(kill(getppid(), SIGUSR1) != 0){
            printf("Ошибка во время отправки SIGUSR1\n"); 
            exit(-1); 
        }
        printf("Успешно отправлен сигнал SIGUSRT1\n"); 

        return 0;
    } 

    wait(NULL);

    while(1){
        pause(); 
    }
}
