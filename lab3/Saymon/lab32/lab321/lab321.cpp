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
// закускаем второй (первая программа)
using namespace std;
int  main()
{
int fd;
int mda;

fd = open("../mypipe",O_WRONLY| O_NONBLOCK); // открываем канал в папке на уровень выше
ifstream in("in.txt"); 
while(in >> mda) // читаем число с файла
write(fd,&mda,sizeof(mda)); // и пишем в канал

close(fd); // закрываем канал
in.close(); // закрыавем файл
return 1;
}