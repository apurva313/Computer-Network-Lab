// Client side C program to demonstrate Socket programming
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib

#define PORT 8080

int main(int argc, char const *argv[]) {
    WSADATA wsaData;
    SOCKET client_fd = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    int status, valread;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error: %d\n", WSAGetLastError());
        return 1;
    }

    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation error. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // Connect to the server
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) == SOCKET_ERROR) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // Send a message to the server
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Read the server's response
    valread = recv(client_fd, buffer, 1024 - 1, 0); // subtract 1 for the null terminator
    if (valread == SOCKET_ERROR) {
        printf("Recv failed. Error: %d\n", WSAGetLastError());
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }
    buffer[valread] = '\0'; // Null-terminate the received data
    printf("%s\n", buffer);

    // Close the connected socket
    closesocket(client_fd);
    WSACleanup();
    return 0;
}
