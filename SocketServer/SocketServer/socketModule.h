#ifndef SOCKETMODULE_H
#define SOCKETMODULE_H

#include <winsock2.h>
#include <ws2tcpip.h>

// Winsock 라이브러리 링크
#pragma comment(lib, "ws2_32.lib")

// Winsock 초기화 함수
int initializeWinsock();

// 소켓 생성 함수
SOCKET createSocket();

// 서버 소켓 바인드 및 리스닝 함수
int bindAndListenSocket(SOCKET socket, int port);

// 클라이언트 소켓 연결 함수
int connectToServer(SOCKET socket, const char* serverIP, int port);

// 데이터 송신 함수
int sendMessage(SOCKET socket, const char* message);

// 데이터 수신 함수
int receiveMessage(SOCKET socket, char* buffer, int bufferLength);

// 소켓 종료 함수
void closeSocket(SOCKET socket);

// Winsock 종료 함수
void cleanupWinsock();

#endif
