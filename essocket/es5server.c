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
int compare(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}
void main()
{
    struct sockaddr_in servizio, addr_remoto;      // record con i dati del client e del server
    int socketfd, soa, fromlen = sizeof(servizio); // identificatore socket
    char str1[DIM], str2[DIM];
    // settaggio socket locale
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // creazione socket e transport endpoint
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // impostazione del transport endpoint del server
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // leghiamo l'indirizzo al transport endpoint
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd, 10); // può attendere fino a 10 client
    // ciclo infinito

    while (1)
    {
        int palindromia = 1;
        printf("server in ascolto......\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        // legge dal client
        read(soa, str1, sizeof(str1));

        printf("Stringa ricevuta: %s\n", str1);
        qsort(str1, strlen(str1), sizeof(char), compare);

        printf("Stringa inviata : %s\n", str1);
        write(soa, str1, strlen(str1));
        close(soa);
    }
    close(soa);
}