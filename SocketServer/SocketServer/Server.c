#include "socketModule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 5500
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int result;

    result = initializeWinsock();
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    SOCKET listenSocket = createSocket();
    if (listenSocket == INVALID_SOCKET) {
        cleanupWinsock();
        return 1;
    }

    result = bindAndListenSocket(listenSocket, SERVER_PORT);
    if (result != 0) {
        closeSocket(listenSocket);
        cleanupWinsock();
        return 1;
    }

    printf("Server is waiting for client connections on port %d...\n", SERVER_PORT);

    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed with error: %ld\n", WSAGetLastError());
        closeSocket(listenSocket);
        cleanupWinsock();
        return 1;
    }

    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE); // Clear buffer
        result = receiveMessage(clientSocket, buffer, BUFFER_SIZE - 1);
        if (result > 0) {
            buffer[result] = '\0'; // Ensure null-terminated
            printf("Client says: %s\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                printf("Exit command received. Closing connection.\n");
                break;
            }

            // 서버가 클라이언트에게 응답을 보냅니다.
            char response[BUFFER_SIZE];
            snprintf(response, BUFFER_SIZE, "Message received: %s", buffer);
            sendMessage(clientSocket, response);
        }
        else if (result == 0) {
            printf("Connection closing...\n");
            break;
        }
        else {
            printf("recv failed: %d\n", WSAGetLastError());
            break;
        }
    }

    closeSocket(clientSocket);
    closeSocket(listenSocket);
    cleanupWinsock();
    return 0;
}
