#include "socketModule.h"
#include <stdio.h>
#include <string.h>

int initializeWinsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

SOCKET createSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed with error: %ld\n", WSAGetLastError());
    }
    return sock;
}

int bindAndListenSocket(SOCKET socket, int port) {
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    if (bind(socket, (struct sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        printf("Bind failed with error: %ld\n", WSAGetLastError());
        return WSAGetLastError();
    }

    if (listen(socket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        return WSAGetLastError();
    }

    return 0; // 성공
}

int connectToServer(SOCKET socket, const char* serverIP, int port) {
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    if (connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connect failed with error: %ld\n", WSAGetLastError());
        return WSAGetLastError();
    }

    return 0; // 성공
}

int sendMessage(SOCKET socket, const char* message) {
    return send(socket, message, strlen(message), 0);
}

int receiveMessage(SOCKET socket, char* buffer, int bufferLength) {
    int bytesReceived = recv(socket, buffer, bufferLength, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Ensure null-terminated string
    }
    return bytesReceived;
}

void closeSocket(SOCKET socket) {
    closesocket(socket);
}

void cleanupWinsock() {
    WSACleanup();
}
