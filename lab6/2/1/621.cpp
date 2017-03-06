/*

*/
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
using namespace std;
struct mymem{ int sum;} *mem_sum;

int main()
{
    int n;
    key_t ipckey;
    ipckey=ftok("/tmp",41);
    int shmid = shmget(ipckey, 2, IPC_CREAT|0666) ;
    if (shmid < 0 ) { fprintf(stdout,"\n Ошибка") ; return 0 ; }
    mem_sum = (mymem *)shmat(shmid,NULL,0) ;
    cout << "Enter n:"; cin >>n;
    mem_sum->sum = n;
    return 1;
}
