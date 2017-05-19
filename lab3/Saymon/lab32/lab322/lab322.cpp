#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>
// запускаем первой (вторая программа)
int IS_prime(double num) // функция проверки на простоту, 0 - если простое,1 - если не простое
{
    int isprime = 0;
    for(int i = 2; i <= sqrt(num); i += 2)
    {
        if(i % 2 == 0)
            i++;

        if((int(num)% i) == 0)
        {
            isprime = 1;
            break;
        }
    }

    return isprime;
}
int main() {
int s;
int fd ;
mkfifo("mypipe",S_IFIFO|0666); // создадим канал
fd = open("mypipe",O_RDONLY); // откроем его
while (read(fd,&s,sizeof(s))) // читаем с канала
{
if(!IS_prime(s)) // если прочтенное простое
fprintf(stdout,"\nПрочитано: '%d'\n",s) ; // выводим в консоль
}
close(fd) ; // закрываем канал
unlink("mypipe") ; // удаляем канал
return 1;
}