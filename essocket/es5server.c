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
        char temp;
        int palindromia = 1;
        printf("server in ascolto......\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        // legge dal client
        read(soa, str1, sizeof(str1));
        str1[strcspn(str1, "\n")] = 0;
        int n = strlen(str1);
        int swapped;

        printf("Stringa ricevuta: %s\n", str1);

        do
        {
            swapped = 0; // Resetta la variabile per controllare se ci sono stati scambi
            for (int i = 0; i < n - 1; i++)
            {
                if (str1[i] > str1[i + 1])
                {
                    // Scambia i caratteri
                    temp = str1[i];
                    str1[i] = str1[i + 1];
                    str1[i + 1] = temp;
                    swapped = 1; // Segnala che è stato effettuato uno scambio
                }
            }
        } while (swapped); // Continua finché ci sono scambi

        printf("Stringa inviata : %s\n", str1);
        write(soa, str1, strlen(str1));
        close(soa);
    }
    close(soa);
}