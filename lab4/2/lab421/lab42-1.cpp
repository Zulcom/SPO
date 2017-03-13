/*
    Cчитать с консоли число и поместить его в очередь сообщений
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
    int n;
    cout << "Enter n: "; cin >> n;
    key_t ipckey;
   ipckey=ftok("/tmp",41);
    msgid = msgget(ipckey, IPC_CREAT|0666) ;
    m.mtype =1;
    m.mdata = n;
    msgsnd(msgid, &m, 2, 0) ;
   m.mdata =0;
    return 1;
}
