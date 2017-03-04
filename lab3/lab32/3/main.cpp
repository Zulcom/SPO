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
#include <iostream>
// run third (first app)
using namespace std;
int  main()
{
int fd;
int mda;
cout << "enter num:";
cin >> mda;
fd = open("../mypipe",O_WRONLY| O_NONBLOCK);
write(fd,&mda,sizeof(mda));
close(fd);
return 1;
}
