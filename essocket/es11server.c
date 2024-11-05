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

    struct sockaddr_in server, client;
    int vettore[arraydim];
    int contpari = 0, contdispari = 0;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0), soa, fromlen = sizeof(server);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport);
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("errore della bind \n");
        close(soa);
    }
    listen(socketfd, 10); // fino a 10 clients
    while (1)
    {
        printf("server in ascolto ....... \n");
        soa = accept(socketfd, (struct sockaddr *)&server, &fromlen);
        if (soa < 0)
        {
            perror("errore soa \n");
            close(soa);
        }
        if (read(soa, vettore, sizeof(vettore)) == -1)
        {
            perror("errore nella lettura del vettore \n");
            close(soa);
        }
        for (int i = 0; i < arraydim; i++)
        {
            if (vettore[i] % 2 == 0)
            {
                contpari++;
            }
            else
            {
                contdispari++;
            }
        }
        printf("cont pari = %d\n", contpari);
        printf("cont dispari = %d\n", contdispari);
        printf("----------------------- \n");
        if (write(soa, &contpari, sizeof(contpari)) == -1)
        {
            perror("errore scrittura al client \n");
            close(soa);
        }
        write(soa, &contdispari, sizeof(contdispari));
    }
    close(soa);
}