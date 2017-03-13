/*
Разработать алгоритм решения задания, с учетом разделения вычислений между несколькими процессами.
Для обмена информацией между процессами использовать разделяемую память.
Для защиты операций с разделяемой памятью и синхронизации процессов использовать семафоры.
Реализовать алгоритм и протестировать его на нескольких примерах
*
Задана строка S, содержащая не менее двух слов. Необходимо найти среди слов,
палиндром максимальной длины. Входные данные: строка S. Для решения задачи
использовать столько процессов, сколько слов в строке.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
using namespace std;
struct mymem{
    int maxsize, i;
};

int main()
{
  string input;
  getline(cin,input);
  istringstream iss(input);
  vector<string> tokens{istream_iterator<string>{iss},
                        istream_iterator<string>{}};
 int shmid = shmget(IPC_PRIVATE,sizeof(mymem),IPC_CREAT|0666);//создаем блок общей памяти, для хранения дескриптора группу семофоров
 int semid = semget(IPC_PRIVATE,1,IPC_CREAT|0666);//функция создает группу семафоров, состоящую из одного семафора

 sembuf plus1 = {0,1,0};//прибавляет единицу к семафору с индексом 0
 sembuf minus1 = {0,-1,0};//отнимает единицу к семафору с индексом 0

 mymem* mem = (mymem*)shmat(shmid,NULL,0);
 mem->maxsize = 0;
 mem->i = -1;
 for(int i=0;i<tokens.size();++i)
    if(fork() == 0){
        semop(semid,&plus1,1);
        if (tokens.at(i) == string(tokens.at(i).rbegin(), tokens.at(i).rend())) {
            if(mem->maxsize < tokens.at(i).length())
                {
                mem->maxsize = tokens.at(i).length();
                    mem->i = i;
                }
             semop(semid,&minus1,1);
        }
       exit(0);
    }
  wait(NULL);
    cout << tokens.at(mem->i);
    return 0;
}
