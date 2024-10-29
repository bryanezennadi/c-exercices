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
#define DimVettore 3
#define SERVERPORT 1313
void main()
{
    struct sockaddr_in servizio, addr_remoto;      // record con i dati del client e del server
    int socketfd, soa, fromlen = sizeof(servizio); // identificatore socket

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
        printf("server in ascolto......\n");
        fflush(stdout);
        int vettore[DimVettore];

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        // legge dal client
        read(soa, vettore, DimVettore);
        int sommapari = 0, sommadispari = 0, countpari=0, countdispari=0;
        float mediapari = 0, mediadispari = 0;
        printf("vettore ricevuto\n");
        for (int i = 0; i < DimVettore; i++)
        {
            if (vettore[i] % 2 == 0)
            {
                printf("%d ", vettore[i]);
                countpari++;
                sommapari = sommapari + vettore[i];
            }
            else
            {
                printf("%d ", vettore[i]);
                countdispari++;
                sommadispari = sommadispari + vettore[i];
            }
        }
        char str2[DIM];
        mediapari = sommapari / countpari;
        mediadispari = sommadispari / countdispari;
        sprintf(str2, "la media dei numeri pari del vettore è: %f e la somma è: %d \n, la somma di quelli dispari è: %d e la media è: %f\n", mediapari, sommapari, sommadispari, mediadispari);
        printf("Stringa inviata : %s\n", str2);
        write(soa, str2, strlen(str2));
        close(soa);
    }
    close(soa);
}