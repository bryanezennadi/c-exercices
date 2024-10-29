#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORTA_SERVER 1313
#define DIMENSIONE_ARRAY 10

int sommaPari(int *array) {
    int somma = 0;
    for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
        if (array[i] % 2 == 0) {
            somma += array[i];
        }
    }
    return somma;
}

int sommaDispari(int *array) {
    int somma = 0;
    for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
        if (array[i] % 2 != 0) {
            somma += array[i];
        }
    }
    return somma;
}

int main(int argc, char **argv) {
    struct sockaddr_in indirizzoServizio, indirizzoClient;
    int socketfd, connessioneAccettata;
    socklen_t lunghezzaClient = sizeof(indirizzoClient);
    int numeri[DIMENSIONE_ARRAY];
    int sommaNumeriPari, sommaNumeriDispari;
    float mediaNumeriPari, mediaNumeriDispari;

    // Configura l'indirizzo del server
    indirizzoServizio.sin_family = AF_INET;
    indirizzoServizio.sin_port = htons(PORTA_SERVER);
    indirizzoServizio.sin_addr.s_addr = htonl(INADDR_ANY);

    // Crea il socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    // Associa il socket all'indirizzo
    if (bind(socketfd, (struct sockaddr *)&indirizzoServizio, sizeof(indirizzoServizio)) < 0) {
        perror("Errore nella bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Inizia ad ascoltare le connessioni
    listen(socketfd, 10);
    printf("Server in ascolto...\n");

    while (1) {
        // Accetta una connessione
        connessioneAccettata = accept(socketfd, (struct sockaddr *)&indirizzoClient, &lunghezzaClient);
        if (connessioneAccettata < 0) {
            perror("Errore nell'accettare la connessione");
            continue;
        }

        // Leggi l'array dal client
        if (read(connessioneAccettata, numeri, sizeof(numeri)) < 0) {
            perror("Errore nella lettura dell'array dal client");
            close(connessioneAccettata);
            continue;
        }

        // Calcola somma e media dei numeri pari
        sommaNumeriPari = sommaPari(numeri);
        mediaNumeriPari = (float)sommaNumeriPari / DIMENSIONE_ARRAY;

        // Calcola somma e media dei numeri dispari
        sommaNumeriDispari = sommaDispari(numeri);
        mediaNumeriDispari = (float)sommaNumeriDispari / DIMENSIONE_ARRAY;

        printf("Somma e media calcolate, pronte per l'invio.\n");

        // Invia i risultati al client
        if (write(connessioneAccettata, &sommaNumeriPari, sizeof(sommaNumeriPari)) < 0) {
            perror("Errore nella scrittura della somma pari al client");
        }
        if (write(connessioneAccettata, &mediaNumeriPari, sizeof(mediaNumeriPari)) < 0) {
            perror("Errore nella scrittura della media pari al client");
        }
        if (write(connessioneAccettata, &sommaNumeriDispari, sizeof(sommaNumeriDispari)) < 0) {
            perror("Errore nella scrittura della somma dispari al client");
        }
        if (write(connessioneAccettata, &mediaNumeriDispari, sizeof(mediaNumeriDispari)) < 0) {
            perror("Errore nella scrittura della media dispari al client");
        }

        // Chiudi la connessione
        close(connessioneAccettata);
    }

    // Chiudi il socket del server
    close(socketfd);
    return 0;
}
