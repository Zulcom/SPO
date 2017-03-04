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
// run first (third app)
int main() {
int s;
int fd ;
mkfifo("mypipe",S_IFIFO|0666);
fd = open("mypipe",O_RDONLY);
read(fd,&s,sizeof(s)) ;
fprintf(stdout,"\nПрочитано: '%d'\n",s) ;
close(fd) ;
unlink("mypipe") ;
return 1;
}
