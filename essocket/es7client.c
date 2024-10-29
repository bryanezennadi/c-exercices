#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define PORTA_SERVER 1313
#define DIMENSIONE_ARRAY 10

void riempiArray(int *array) {
    srand((unsigned)time(NULL)); // Inizializza il generatore di numeri casuali
    for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
        array[i] = rand() % 101; // Genera numeri casuali tra 0 e 100
        printf("%d ", array[i]); // Stampa il numero generato
    }
}

int main(int argc, char **argv) {
    struct sockaddr_in indirizzoServizio;
    int socketfd, lunghezza = sizeof(indirizzoServizio);
    int numeri[DIMENSIONE_ARRAY];
    int sommaPari, sommaDispari;
    float mediaPari, mediaDispari;

    // Configura l'indirizzo del server
    indirizzoServizio.sin_port = htons(PORTA_SERVER);
    indirizzoServizio.sin_family = AF_INET;
    indirizzoServizio.sin_addr.s_addr = htonl(INADDR_ANY);

    // Crea un socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // Connessione al server
    if (connect(socketfd, (struct sockaddr *)&indirizzoServizio, lunghezza) < 0) {
        perror("Errore nella connessione");
        exit(EXIT_FAILURE);
    }

    // Riempi l'array con numeri casuali
    riempiArray(numeri);

    // Invia l'array al server
    if (write(socketfd, numeri, DIMENSIONE_ARRAY * sizeof(int)) < 0) {
        perror("Errore nella scrittura dell'array al server");
        exit(EXIT_FAILURE);
    }

    printf("\nArray inviato al server\n");

    // Ricevi la somma dei numeri pari dal server
    if (read(socketfd, &sommaPari, sizeof(sommaPari)) < 0) {
        perror("Errore nella lettura della somma dal server");
        exit(EXIT_FAILURE);
    }

    // Ricevi la media dei numeri pari dal server
    if (read(socketfd, &mediaPari, sizeof(mediaPari)) < 0) {
        perror("Errore nella lettura della media dal server");
        exit(EXIT_FAILURE);
    }

    // Ricevi la somma dei numeri dispari dal server
    if (read(socketfd, &sommaDispari, sizeof(sommaDispari)) < 0) {
        perror("Errore nella lettura della somma dal server");
        exit(EXIT_FAILURE);
    }

    // Ricevi la media dei numeri dispari dal server
    if (read(socketfd, &mediaDispari, sizeof(mediaDispari)) < 0) {
        perror("Errore nella lettura della media dal server");
        exit(EXIT_FAILURE);
    }

    // Stampa i risultati
    printf("Media numeri pari: %.2f, media numeri dispari: %.2f\n", mediaPari, mediaDispari);
    printf("Somma numeri pari: %d, somma numeri dispari: %d\n", sommaPari, sommaDispari);

    // Chiudi il socket
    close(socketfd);
    return 0;
}
