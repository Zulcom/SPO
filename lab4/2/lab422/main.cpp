/*
   Умножить число в очереди сообщений на два.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
using namespace std;
int  msgid;
//для хранения дескриптора очереди сообщений
//массив, сумма элементов которого вычисляется процессами
struct mymsg{ //структура для сообщений
  int mtype;  //тип сообщения(может требоваться тип long, а не int)
  int mdata; //данные сообщения
} m ;

int  main() {
    key_t ipckey;
    ipckey=ftok("/tmp",41);
    msgid =msgget(ipckey,0);
    m.mtype =1;
    msgrcv(msgid, &m, 2, 0, 0) ;
     cout << m.mdata;
    m.mdata=m.mdata*2 ;
    msgsnd(msgid, &m, 2, 0) ;
    return 1;
}
