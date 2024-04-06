#ifndef SOCKETMODULE_H
#define SOCKETMODULE_H

#include <winsock2.h>
#include <ws2tcpip.h>

// Winsock ���̺귯�� ��ũ
#pragma comment(lib, "ws2_32.lib")

// Winsock �ʱ�ȭ �Լ�
int initializeWinsock();

// ���� ���� �Լ�
SOCKET createSocket();

// ���� ���� ���ε� �� ������ �Լ�
int bindAndListenSocket(SOCKET socket, int port);

// Ŭ���̾�Ʈ ���� ���� �Լ�
int connectToServer(SOCKET socket, const char* serverIP, int port);

// ������ �۽� �Լ�
int sendMessage(SOCKET socket, const char* message);

// ������ ���� �Լ�
int receiveMessage(SOCKET socket, char* buffer, int bufferLength);

// ���� ���� �Լ�
void closeSocket(SOCKET socket);

// Winsock ���� �Լ�
void cleanupWinsock();

#endif
