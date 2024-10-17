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
void main()
{
    struct sockaddr_in servizio;
    int socketfd; // identificatore socket
    char str1[DIM];
    // settaggio socket locale
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // creazione socket e transport endpoint
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // richiesta connessione al server
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    printf("inserisci la stringa\n");
    fgets(str1, DIM, stdin); // uso l'fgets perchè lo scanf non legge gli spazi
    // leggo dal server
    write(socketfd, str1, sizeof(str1));
    int lunghezzastringa = strlen(str1);
    // leggo dal server
    read(socketfd, str1, strlen(str1));
    int contatore= atoi(str1);
   
    printf("il totale delle vocali sono: %d \n", contatore);
    printf("il totale delle consonanti sono: %d \n", lunghezzastringa-contatore-1); //levo alla stringa totale il numero delle vocali ed il carattere terminatore
    close(socketfd);
}