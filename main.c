#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("Client started.\n");

    const char *hostName = "192.168.137.1";
    const char *portNumber = "8808";
    int clientSocket;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    struct addrinfo *results;
    struct addrinfo *record;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ((getaddrinfo(hostName, portNumber, &hints, &results)) != 0) {
        perror("Failed to translate client socket.");
        exit(EXIT_FAILURE);
    }

    printf("Client socket translated.\n");

    for (record = results; record != NULL; record = record->ai_next) {
        clientSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
        if (clientSocket == -1) continue;
        if (connect(clientSocket, record->ai_addr, record->ai_addrlen) != -1) break;
        close(clientSocket);
    }

    if (record == NULL) {
        perror("Failed to create or connect client socket.");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(results);

    printf("Client socket created and connected.\n");

    char *message = "test message from client";

    if (send(clientSocket, message, strlen(message), 0) == -1) {
        perror("Failed to perform cognitive recalibration.");
        exit(EXIT_FAILURE);
    } else {
        printf("Message sent to server.\n");
    }

    close(clientSocket);

    printf("Client socket closed.\n");

    return 0;
}
