
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
#include <ctime>
int main()
{
    int sock;
    struct sockaddr_in server;
    char message[100],server_reply;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)

        printf("Could not create socket");

    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 1582);

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");
    int read_size =0;
    if((read_size = recv(sock , &server_reply ,sizeof(char) , 0))< 0)
    {
        puts("recv failed");
    }
    if(server_reply == '0')
    printf("Новая игра!\n");
    while(1)
    {
    printf("Хочешь вытянуть мяч?(д/н) : ");
        scanf("%s" , message);
        if(message[0] == 'н') return 0;
        srand(time(0));
        char hod[1];
        hod[0] = '1';
        printf("Ошидаем ход соперника\n");
        //Send some data
        if( send(sock , hod , sizeof(char) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        //Receive a reply from the server
        if((read_size = recv(sock , &server_reply ,sizeof(char) , 0))< 0)
        {
            puts("recv failed");
            break;
        }
      if(server_reply == '3'){  printf("Вы выиграли!\n"); break;};
      if(server_reply == '2'){  printf("Победил соперник\n");break;};
      if(server_reply == '4'){  printf("Ничья\n");break;};
      if(server_reply == '1')printf("Нужно совершить следующий ход\n");
    }
    close(sock);
    return 0;
}

