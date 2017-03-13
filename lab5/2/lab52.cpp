#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
using namespace std;
void theend (int sig){  exit (0);}

int main(){
// Init

  int fd[2];
  if (pipe(fd)<0){  cout << "\n Ошибка создания канала";return 0;}
  int n,k,death,tempReader,counter = 0; //кол-во чисел, кол-во потоков, время жизни, буфер чтения с консоли и счётчик 0/1
  char whatsCount; // что считать?

// Console dialogs
  cout << "enter n:" <<endl;
  cin >> n;
  cout << "enter k: "; cin >>k;
  cout << "count zeros or ones (z/o) ";
  cin >> whatsCount;
  int * a = new int[n];
  for(int i=0;i<n;i++) {
      cin >> tempReader;
      a[i] = (tempReader < 0);
      write(fd[1],&tempReader,sizeof(tempReader));
  }
  cout << "Время жизни: ";
  cin >> death;

// Logic
  bool countZero = whatsCount == 'z';
  struct sigaction act;
  act.sa_handler = theend;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction (SIGALRM, &act, 0);
  alarm (death);

// threads
  for(int i=0;i<k;i++)
  if (fork()==0){
    for(int j = 0;j< n/k;++j){
    int temp;
    read(fd[0],&temp,4);
    cout << (temp < 0);
    }
    return 1;
  }

// Console out
  for(int i=0;i<n;++i)
      if(countZero && a[i] == 0) counter++;
       else if(!countZero && a[i] == 1) counter++;
  cout <<"\nCounter:" <<counter << "\n";
  return 0;
}
