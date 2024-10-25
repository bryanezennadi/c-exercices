#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#define DIM 512
#define SERVERPORT 1313
#define DimVettore 3
void main()
{
    struct sockaddr_in servizio;
    int socketfd; // identificatore socket
    int vettoreNumeri[DimVettore];
    vettoreNumeri[0] = 4;
    vettoreNumeri[1] = 7;
    vettoreNumeri[2] = 10;
    for (int i = 0; i < DimVettore ;i++)
    {
        printf("%d \n", vettoreNumeri[i]);
    }
    // settaggio socket locale
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // creazione socket e transport endpoint
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // richiesta connessione al server
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    write(socketfd, vettoreNumeri, DimVettore);
    char str1[DIM];
    read(socketfd, str1, sizeof(str1));
    printf("%s \n", str1);
    close(socketfd);
}