#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEF_F_R "from.txt"
#define DEF_F_W "to.txt"

int main(int argc, char** argv) {
    char fileToRead[32],
    fileToWrite[32];
    if(argc < 3 ){
        printf("Используем стандартные имена файлов '%s','%s'\n",DEF_F_R,DEF_F_W);
        strcpy(fileToRead,DEF_F_R);
        strcpy(fileToWrite,DEF_F_W);
    }
    else {
        strcpy(fileToRead,argv[1]);
        strcpy(fileToWrite,argv[2]);
    }
    
    int filedes[2];
    if(pipe(filedes) < 0) {
        printf("Родитель: не может создать канал\n");
        exit(1);
    }
    printf("Канал успешно создан\n");
    if(fork() == 0) {
// процесс сын
// закрывает пайп для чтения
        close(filedes[0]);
        FILE* f = fopen(fileToRead,"r");
        if (!f){
            printf("Сын: не может открыть файл%s\n",fileToRead);
            exit(1);
        }
        char buf[100];
        int res;
        while(!feof(f)) {
            // читаем данные из файла
            res = fread(buf,sizeof(char),100,f);
            write(filedes[1],buf,res); // пишем их в пайп
        }
        close(f);
        close(filedes[1]);
         return 0;
    }
// процесс отец
// закрывает пайп для записи
     close(filedes[1]);
     FILE *f = fopen(fileToWrite,"w");
    if (!f) {
    printf("Родитель: не может открыть файл %s\n",fileToWrite);
    exit(1);
    }
    
    char buf[100];
    int res;
    while(1) {
        bzero(buf,100);
        res = read(filedes[0],buf,100);
        if(!res)
            break;
        printf("Считывание из канал: %s\n",buf);
        fwrite(buf,sizeof(char),res,f);
    }
    fclose(f);
    close(filedes[0]);
    return 0;
}