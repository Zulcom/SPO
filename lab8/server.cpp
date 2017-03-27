/*
	 Пожалуйста, используйте данный код исключииельно в ознакомительных целях.
	 Код отвратителен как по стилю написания, так и по функциональности. 
	 Вряд ли он заработает где-либо помимо моей среды разработки.
	 Заранее извиняюсь за свою безответственность.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <iomanip>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
struct mymem{
    int players[2];
    int box[8];
};
int main()
{
    srand(time(0));
    int socket_desc , client_sock , c , new_sock;
    struct sockaddr_in server , client;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) 
        printf("Could not create socket");  
    puts("Socket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons( 1582 );
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    //Listen
    listen(socket_desc , 3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    int shmid = shmget(IPC_PRIVATE,sizeof(mymem),IPC_CREAT|0666);//создаем блок общей памяти, для хранения дескриптора группу семофоров
    int semid = semget(IPC_PRIVATE,1,IPC_CREAT|0666);//функция создает группу семафоров, состоящую из одного семафора
    sembuf plus1 = {0,1,0};//прибавляет единицу к семафору с индексом 0
    sembuf minus1 = {0,-1,0};//отнимает единицу к семафору с индексом 0
     mymem* mem = (mymem*)shmat(shmid,NULL,0);
    // for(int i=0;i<8;++i)
     memset(mem->box,0,sizeof(mem->box));
     int temp = rand()%9;
     mem->box[temp] = 1;
     temp = temp + rand()%(9-temp);
     mem->box[rand()%9] = 1;
    printf("%d %d %d %d %d %d %d %d\n",mem->box[0],mem->box[1],mem->box[2],mem->box[3],mem->box[4],mem->box[5],mem->box[6],mem->box[7]);
    mem->players[0]=-1; mem->players[1]=-1;
    for(int b=0;b<2;++b) //создаём два подключения
    {
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        puts("Connection accepted");
        new_sock  = client_sock;
        if(fork() == 0)
        {
            int sock =new_sock;
            int read_size;
            char  client_message;
            char welcome = '0';
            write(sock , &welcome , sizeof(char));
            char hod = '0';

            mem->players[0]= -1;
            mem->players[1]=-1;
            while( (read_size = recv(sock , &client_message , sizeof(char) , 0)) > 0 )
            { 
                int thisPlayer =-1;
                // вытягиваем из коробки шар
                semop(semid,&plus1,1);

                if(mem->players[0] == -1 ||mem->players[0]+mem->players[1] ==1 ) {
                    for(int i=0;i<8;++i) if(mem->box[i] != -1){ mem->players[0] = mem->box[i];mem->box[i]=-1;break;}
                    thisPlayer = 0;
                }
                else if(mem->players[1] == -1 || mem->players[0]+mem->players[1] == 1) {
                    for(int i=7;i>0;--i) if(mem->box[i] != -1){ mem->players[1] =  mem->box[i];mem->box[i]=-1;break;}
                    thisPlayer = 1;
                }
                 printf("%d %d %d %d %d %d %d %d\n",mem->box[0],mem->box[1],mem->box[2],mem->box[3],mem->box[4],mem->box[5],mem->box[6],mem->box[7]);
                  semop(semid,&minus1,1);
               while(mem->players[0] == -1 || mem->players[1] == -1) sleep(1);
               if(mem->players[0] == mem->players[1] && mem->players[1] == 1) hod = '4';
               if(mem->players[0] ^ mem->players[1])
               {
                   if(mem->players[thisPlayer]==1) hod = '3';
                   else hod = '2';
               }

               if(mem->players[0] == mem->players[1] && mem->players[0] == 0  )
                   hod='1';

               send(sock , &hod, sizeof(char),0);
              sleep(1);if(hod = '1'){mem->players[0] = -1; mem->players[1] = -1;}
            }
            if(read_size == 0)
            {
                puts("Client disconnected");
                printf("%d %d\n",mem->players[0],mem->players[1]);
                 fflush(stdout);
                close(sock);
            }
            else if(read_size == -1)

                perror("recv failed");

            return 0;
        }
        puts("Handler assigned");
    }
    return 0;
}
