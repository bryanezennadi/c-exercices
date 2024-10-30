#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define PortaServer 1313
#define ArrayDim 100
void main()
{
    struct sockaddr_in serveraddr, clientaddr;
    int socketfd, soa, fromlen = sizeof(serveraddr);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PortaServer);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(socketfd, 10);
    while (1)
    {
        printf("server in ascolto.................\n");
        fflush(stdout);
        char str1[ArrayDim], str2[ArrayDim], str3[ArrayDim];
        soa = accept(socketfd, (struct sockaddr *)&clientaddr, &fromlen);
        read(soa, str1, sizeof(str1));
        printf("prima stringa ricevuta dal client: %s\n", str1);
        read(soa, str2, sizeof(str2));
        printf("seconda stringa ricevuta dal client: %s\n", str2);
        if (strlen(str1) > strlen(str2))
        {
            sprintf(str3, "la stringa più lunga è la prima");
        }
        else if (strlen(str1) == strlen(str2))
        {
            sprintf(str3, "le due stringhe hanno la stessa lunghezza");
        }
        else
        {
            sprintf(str3, "la stringa più lunga è la seconda");
        }
        printf("Stringa inviata al client: %s\n", str3);
        write(soa, str3, strlen(str3));
        close(soa);
        printf("-------------------------------------\n");
    }
    close(soa);
}