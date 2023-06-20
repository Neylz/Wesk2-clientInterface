#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <winsock.h>

#define SERVER_IP "192.168.1.13"  // Replace with the server IP address
#define SERVER_PORT 12345      // Replace with the server port number

void send_request(int client_socket, const char* request) {
    // Send the request to the server
    write(client_socket, request, strlen(request));
}

void receive_response(int client_socket) {
    char response[1024];
    memset(response, 0, sizeof(response));

    // Receive the response from the server
    read(client_socket, response, sizeof(response));

    // Process the response (e.g., perform actions based on the response)
    printf("Received response from server: %s\n", response);
}

int main() {
    // Create a socket for the client
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address and port
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    // Convert IP address from text to binary format
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send the data to the server
    const char* data = "Data to be sent to the server";
    send_request(client_socket, data);

    // Receive and process the server response
    receive_response(client_socket);

    // Close the socket
    close(client_socket);

    return 0;
}
