#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
int main()
{
  int x=0;
  while(x!=4)
  {
    printf ("1.Выполнить введённую команду\n");
    printf ("2.Запустить на исполнение файл со сценарием\n");
    printf ("3.Завершить процесс с указанным именем\n");
    printf ("4.Выход\n");
    scanf("%d",&x);
    pid_t pid;
    int rv;
    switch (x)
    {
      case 1:
      {
        pid = fork();
        if(pid != 0){
         printf("Введите нужную команду\n");
         string s;
         cin.get();
         getline(cin, s);
         system(s.c_str());
        } else exit(0);


      }break;
      case 2:
      {
    pid = fork();
      if(pid != 0){
        system("bash laba1.bash");
    }else exit(0);
      }break;
      case 3:
      {
    pid = fork();
      if(pid != 0){
        cout << "\nВведите имя процесса: ";
        string name, command;
        cin.get();
        getline(cin, name);
        command = "killall " + name;
        system(command.c_str());
        printf("\n");
      } else exit(0);
      }break;
      case 4:
      {
    return 0;
      }break;
    }
  }
  return 0;
}