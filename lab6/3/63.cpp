/*
Задан массив односвязных списков.
Вывести на экран список, содержащий максимальное количество положительных чисел
*/
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
#define NUMSTACK 5000 //объем стека для отдельного потока
vector<int> A[100] ; //массив, сумма элементов которого вычисляется процессами
int MAX=0,iMAX =0;
char stack[4][ NUMSTACK] ; //для хранения стека четырех потоков
int func(void *param)  //стартовая функция потоков
{
    int  i ;
    int p =*(int *)param;
    p=p*25 ;
    int positive = 0, ipos = 0;
    for(i=p ; i<p+25 ; i++){
      int tempPosSum =0;
      cout << i+1 << ": ";
      for(int j :A[i])
      {
         cout << j << " ";
         if(j>0) tempPosSum+=j;
      }
      if(tempPosSum>positive){
          positive = tempPosSum;
          ipos = i;
      }
      cout << " ("<< positive << ")\n";
    }
    if(positive > MAX)
    {
        MAX = positive;
        iMAX = ipos;
    }
    return 1 ;
}
int  main()
{
    srand(time(0));
    vector<int> temp;
    for(int i=0;i<100;++i){
      for(int i=0;i<5;i++)  temp.push_back(rand()%1000);
        A[i] = temp;
        temp.clear();
    }
    int param[4];
    for(int i=0 ; i<3 ; i++) //создание трех потоков
    {
        param[i]=i ;
        char *tostack=stack[i] ;
        clone(func,(void*)( tostack+ NUMSTACK -1),CLONE_VM, (void *)(param+i)) ;
        sleep(1);
    }
    param[3]=3 ;
    char* tostack = stack[3] ;
    clone(func,(void*)( tostack+ NUMSTACK -1), CLONE_VM|CLONE_VFORK, (void *)(param+3)) ;
    fprintf (stdout,"\nПервая самая большая сумма найдена в строке %d: \n",iMAX+1) ;
    for(int i: A[iMAX]) cout << i << " ";
    cout << " (" << MAX << ")\n";
    return 1 ;
}
