/*
    В массиве А заменить положительные элементы нулями, а отрицательные элементы единицами.
    Определить число вхождений в массиве нулей или единиц по указанию пользователя в начале работы программы.
    Входные данные: целое положительное число n, массив чисел А размерности n, целое положительное число к ≥ 2 и ≤ n/2, поиск нулей или единиц.
    Использовать для решения задачи к процессов.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
using namespace std;
int  msgid;
int  * A;
int  step;
struct mymsg{ 
  int mtype;  
  int mdata; 
} m ;
int summa(int p,int whatsCount) 
{
    int i,sum = 0 ;
    int begin = step*p ;
    int end   = begin+step ;
    for(i=begin ; i<end ; i++){
        A[i] = A[i] > 0 ? 0 : 1;
        fprintf(stdout,"\nA[%d]=%d\n",i,A[i]);
        if(whatsCount && A[i]) sum++;
        else if(!whatsCount && !A[i]) sum++;
    }
    m.mtype = 1;
    m.mdata = sum;
    msgsnd(msgid, &m, 2, 0) ;
    return sum ;
}
int  main() {
    int n;
    cout << "Enter n: "; cin >> n;
    A = new int[n];
    for(int i=0;i<n;++i){ cout <<"A["<< i << "]=";cin >>A[i];}
    int k;
    cout << "Enter k:"; cin >> k;
    int whatsCount;
    cout << "Count zeros or ones? (0/1):"; cin >> whatsCount;
    msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666) ;
    if (msgid < 0 ) { fprintf(stdout,"\nОшибка создании очереди") ; return 0 ; }
    step = n/k;
    for (int  i=0 ; i<k ; i++) 
        if  ( fork() == 0 ) { summa(i,whatsCount) ; return 1 ; } 
    int rez = 0;
    for(int i=0 ; i<k ; i++)
    {
        msgrcv(msgid, &m, 2, 0, 0) ;
        rez+= m.mdata ;
    }
    sleep(2);
    fprintf(stdout,"\nЧисло вхождений =  %d\n",rez) ;
    return 1;
}