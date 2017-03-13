/*
  напечатать число из очереди
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

int main() {
    key_t ipckey;
    ipckey=ftok("/tmp",41);
    msgid =msgget(ipckey,0);
    msgrcv(msgid, &m, 2, 0, 0) ;
    fprintf(stdout," yep : %d",m.mdata);
    return 1;
}
