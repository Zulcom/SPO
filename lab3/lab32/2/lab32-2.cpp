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
// run second (second app)
int main() {
int s;
int fd ;
fd = open("../../mypipe",O_RDWR);
int y;
read(fd,&y,sizeof(y)*15);
int mda =y*2;
write(fd,&mda,sizeof(s));
fprintf(stdout,"\nWriten: '%d'\n",mda) ;
close(fd);
return 1;
}
