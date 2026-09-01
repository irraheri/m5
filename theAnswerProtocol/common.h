#include <arpa/inet.h>  // 'inter'-net
#include <netdb.h>      // ipaddr
#include <netinet/in.h> // sockaddr_in AF_INET SOCK_STREAM INADDR_ANY htons
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket, bind, listen, accept, recv, send, close
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_PLAYER 12
