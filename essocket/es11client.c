#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#define serverport 1313
#define arraydim 4
void main()
{
    int contpari = 0, contdispari = 0;
    int array[arraydim];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;

    struct sockaddr_in servizio;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd <0){
        perror("errore creazione socket");
        close(socketfd);
    }
    servizio.sin_port = htons(serverport);
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    if(connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio))==-1){
        perror("errore connessione al server\n");
        close(socketfd);
    }
    if(write(socketfd, array, sizeof(array)) == -1){
        perror("errore scrittura nella socket\n");
        close(socketfd);
    }
    if(read(socketfd, &contpari, sizeof(contpari))== -1){
        perror("errore lettura contatore numeri pari\n");
        close(socketfd);
    }
    read(socketfd, &contdispari, sizeof(contdispari));
    printf("il totale di numeri pari nell'array è: %d \n", contpari);
    printf("il totale di numeri dispari nell'array è: %d \n", contdispari);

    close(socketfd);
}