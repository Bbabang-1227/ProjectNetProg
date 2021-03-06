//cmyclient.cpp
#include "pch.h"

#include <stdio.h>
#include <ws2tcpip.h>	//inet_pton
#include "CMyClient.h"

CMyClient::CMyClient() : sock(0)
{
	//1. 라이브러리 초기화(Winsock 2.2버전)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		exit(-1);
	}
}

CMyClient::~CMyClient()
{
	//2. 라이브러리 해제
	WSACleanup();
}

void CMyClient::CreateSocket(const char* ip, int port)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw "소켓 생성 오류";

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	unsigned int numberaddr;
	inet_pton(AF_INET, ip, &numberaddr);
	addr.sin_addr.s_addr = numberaddr;
	int retval = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		throw "서버 연결 실패";

	//수신 Thread생성하는 위치
	CloseHandle(CreateThread(0, 0, RecvThread, (LPVOID)sock, 0, 0));
}

void CMyClient::SendData(const char* msg, int length)
{
	int retval1 = send(sock, msg, length, 0);
	printf("   [송신] %dbyte\n", retval1);
}

DWORD __stdcall CMyClient::RecvThread(LPVOID value)
{
	SOCKET sock = (SOCKET)value;
	while (true)
	{
		//수신
		char buf[256];
		int retval = recv(sock, buf, sizeof(buf), 0);
		if (retval == -1 || retval == 0)
		{
			printf("소켓 오류 or 상대방이 종료함\n");
			closesocket(sock);
			return 0;
		}

		buf[retval] = '\0'; //상대방이 넘길때 strlen()만큼만 넘겼다고 가정!
		printf(">> [수신데이터] %s\n", buf);
	}

	return 0;
}