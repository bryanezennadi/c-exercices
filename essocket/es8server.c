#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORTA_SERVER 1313
#define DIMENSIONE_ARRAY 10

int TrovaMassimo(int *array) {
    int massimo = array[0];
    for (int i = 1; i < DIMENSIONE_ARRAY; i++) {
        if (array[i] > massimo) {
            massimo = array[i];
        }
    }
    return massimo;
}

int TrovaMinimo(int *array) {
    int minimo = array[0];
    for (int i = 1; i < DIMENSIONE_ARRAY; i++) {
        if (array[i] < minimo) {
            minimo = array[i];
        }
    }
    return minimo;
}

int main(int argc, char **argv) {
    struct sockaddr_in indirizzoServizio, indirizzoClient;
    int socketfd, connessioneAccettata;
    socklen_t lunghezzaClient = sizeof(indirizzoClient);
    int numeri[DIMENSIONE_ARRAY];
    int massimo, minimo;

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

        // Calcola massimo e minimo
        massimo = TrovaMassimo(numeri);
        minimo = TrovaMinimo(numeri);
        printf("Massimo e minimo calcolati, pronto per l'invio.\n");

        // Invia i risultati al client
        if (write(connessioneAccettata, &massimo, sizeof(massimo)) < 0) {
            perror("Errore nella scrittura del massimo al client");
        }
        if (write(connessioneAccettata, &minimo, sizeof(minimo)) < 0) {
            perror("Errore nella scrittura del minimo al client");
        }

        // Chiudi la connessione
        close(connessioneAccettata);
    }

    // Chiudi il socket del server
    close(socketfd);
    return 0;
}
