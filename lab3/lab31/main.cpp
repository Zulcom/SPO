#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
using namespace std;
int main()
{
  int fd[2];
  int n; cout << "enter n:" <<endl;
  cin >> n;
  int k;
  cout << "enter k: "; cin >>k;
  cout << "count zeros or ones (z/o) ";
  char whatsCount;
  cin >> whatsCount;
  bool countZero= whatsCount == 'z';
  if (pipe(fd)<0)
  {
    cout << "\n Ошибка создания канала";
    return 0;
  }
  int tempReader;
  int * a = new int[n];
  for(int i=0;i<n;i++) {
      cin >> tempReader;
      a[i] = (tempReader < 0);
      write(fd[1],&tempReader,sizeof(tempReader));
  }
  for(int i=0;i<k;i++)
  if (fork()==0)
  {
    for(int j = 0;j< n/k;++j){
    int temp;
    read(fd[0],&temp,4);
    cout << (temp < 0);
    }
    return 1;
  }
  int counter = 0;
  for(int i=0;i<n;++i)
      if(countZero && a[i] == 0) counter++;
       else if(!countZero && a[i] == 1) counter++;
  cout <<"\nCounter:" <<counter << "\n";
  return 0;
}
