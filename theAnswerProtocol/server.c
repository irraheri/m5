#include <unistd.h>

#include <stdlib.h>

#include <stdio.h>

#include <sys/socket.h> // socket, bind, listen, accept, recv, send, close
#include <netinet/in.h> // sockaddr_in AF_INET SOCK_STREAM INADDR_ANY htons

#include <pthread.h>

#include <netdb.h>
#include <arpa/inet.h>

#include <string.h>

#define PORT 8080

void *client_host(void *arg)
{
    int client_id = *(int *)arg;
    char buf[1024];

    // recv: attente bloquante, seulement si recoit: send OK au clients
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        recv(client_id, buf, 1024, 0);
        printf("RECEIVED %s from socket %d\n", buf, client_id);
        // client manokana
        send(client_id, "OK\n", 3, 0);
    }
    close(client_id);
    return NULL;
}

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    
    struct hostent *host_entry;
    char hostname[256];
    char ip[INET_ADDRSTRLEN];

    gethostname(hostname, sizeof(hostname));
    printf("NOM DE L'HOTE: %s\n", hostname);
    host_entry = gethostbyname(hostname);
    if (host_entry)
    {
        inet_ntop(AF_INET, host_entry->h_addr_list[0], ip, sizeof(ip));
        printf("IP du serveur: %s\n\n", ip);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address)); // brancher s sur a
    listen(server_fd, 5); // active l'ecoute, 5 clients au max

    // a partir de la on a un serveur!
    while(1)
    {
        int *c = malloc(sizeof(int));
        // attente blocante!
        *c = accept(server_fd, NULL, NULL);
        printf("==================\nCLIENT %d connecté\n==================\n", c[0]);
        // chaque client = c

        pthread_t t;
        pthread_create(&t, NULL, client_host, c);
        // execution de f pour chaque thread, multiclient!!
        pthread_detach(t);
        // fin
    }
    close(server_fd);
}
