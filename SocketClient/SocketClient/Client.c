#include "socketModule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5500
#define BUFFER_SIZE 1024

int main() {
    char message[BUFFER_SIZE];
    int result;

    result = initializeWinsock();
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    SOCKET connectSocket = createSocket();
    if (connectSocket == INVALID_SOCKET) {
        cleanupWinsock();
        return 1;
    }

    result = connectToServer(connectSocket, SERVER_IP, SERVER_PORT);
    if (result != 0) {
        closeSocket(connectSocket);
        cleanupWinsock();
        return 1;
    }

    printf("Connected to server. Type 'exit' to close connection.\n");

    do {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline character
        if (strcmp(message, "exit") == 0) break;

        sendMessage(connectSocket, message);

        memset(message, 0, BUFFER_SIZE); // Clear buffer
        result = receiveMessage(connectSocket, message, BUFFER_SIZE - 1);
        if (result > 0) {
            message[result] = '\0';
            printf("Echo from server: %s\n", message);
        }
        else {
            printf("Server connection closed.\n");
            break;
        }
    } while (1);

    closeSocket(connectSocket);
    cleanupWinsock();
    return 0;
}
