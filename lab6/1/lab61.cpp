/*
Найти максимальный элемент из минимальных элементов в каждой строке  матрицы А.
Входные данные: целое положительное число n, целое положительное число к, массив чисел от А размерности nxк.
Использовать n или n+1 процессов для решения задачи
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
    int n,k;
    int shmid = shmget(IPC_PRIVATE, 2, IPC_CREAT|0666) ;
    if (shmid < 0 ) { fprintf(stdout,"\n Ошибка") ; return 0 ; }
    mem_sum = (mymem *)shmat(shmid,NULL,0) ;
    cout << "Enter n:"; cin >>n;
    cout << "Enter k:"; cin >>k;
    mem_sum->sum = INT8_MIN;
    for(int i=0;i<k;++i)
    {
        if ( fork() == 0)
        {
            int min,temp;
            cin >> min;
            for (int j=0 ; j<n-1 ; j++){
                cin >> temp;
                min = (temp < min ? temp : min);
            }
            mem_sum->sum = (mem_sum->sum < min ? min: mem_sum->sum);
           return 0;
        }
        wait(NULL);
    }
    fprintf(stdout,"\nРезультат =  %d\n",mem_sum->sum);
    return 1;
}
