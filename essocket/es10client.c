#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#define ArrayDim 100
#define portaserver 1313
void main()
{
    struct sockaddr_in servizio;
    int socketfd;
    char str1[ArrayDim], str2[ArrayDim], str3[ArrayDim];
    printf("inserisci prima stringa\n");
    scanf("%s", str1);
    printf("inserisci seconda stringa\n");
    scanf("%s", str2);
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(portaserver);
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    write(socketfd, str1, sizeof(str1));
    write(socketfd, str2, sizeof(str2));
    read(socketfd, str3, sizeof(str3));
    printf("%s \n", str3);
    close(socketfd);
}