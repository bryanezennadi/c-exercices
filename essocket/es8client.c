#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define PORTA 1313
#define DIMENSIONE_ARRAY 10

void riempiArray(int *array) {
    srand((unsigned)time(NULL)); // Inizializza il generatore di numeri casuali
    for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
        array[i] = rand() % 101; // Genera numeri casuali tra 0 e 100
        printf("%d ", array[i]); // Stampa il numero generato
    }
}

int main(int argc, char **argv) {
    struct sockaddr_in indirizzoServer;
    int socketfd, lunghezzaIndirizzo = sizeof(indirizzoServer);
    int numeri[DIMENSIONE_ARRAY];
    int massimo, minimo;

    // Imposta la struttura dell'indirizzo del server
    indirizzoServer.sin_port = htons(PORTA);
    indirizzoServer.sin_family = AF_INET;
    indirizzoServer.sin_addr.s_addr = htonl(INADDR_ANY);

    // Crea un socket TCP
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Creazione del socket fallita");
        exit(EXIT_FAILURE);
    }

    // Connessione al server
    if (connect(socketfd, (struct sockaddr *)&indirizzoServer, lunghezzaIndirizzo) < 0) {
        perror("Errore di connessione");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Riempi l'array con numeri casuali
    riempiArray(numeri);

    // Invia l'array al server
    if (write(socketfd, numeri, DIMENSIONE_ARRAY * sizeof(int)) < 0) {
        perror("Invio dell'array al server fallito");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("\nArray inviato al server con successo.\n");

    // Ricevi il valore massimo dal server
    if (read(socketfd, &massimo, sizeof(massimo)) < 0) {
        perror("Errore nella lettura del valore massimo dal server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Ricevi il valore minimo dal server
    if (read(socketfd, &minimo, sizeof(minimo)) < 0) {
        perror("Errore nella lettura del valore minimo dal server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Mostra i risultati
    printf("MAX: %d\n", massimo);
    printf("MIN: %d\n", minimo);

    // Chiudi il socket
    close(socketfd);
    return 0;
}
