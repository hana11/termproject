#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>

// -------------------- client -----------------------

int main(void)
{
	int iSock;
	struct sockaddr_in staddr;
	int iRet;
	unsigned char ucBuff[250];

	// IPv4를 사용하고 TCP방식 사용하는 소켓을 생성
	iSock = socket(AF_INET,SOCK_STREAM,0);

	if(0 > iSock) // 에러발생시
	{
		perror("socket() ");
		return 0;
	}

	staddr.sin_family 	= AF_INET;
	staddr.sin_port		= htons(PORT); // '4030'번 port에 접속할 예정이다.
	staddr.sin_addr.s_addr		= inet_addr("192.168.10.250"); // 문자열(IP)를 int로 바꾸어주는 함수

	iRet = connect(iSock,(struct sockaddr*)&staddr,sizeof(staddr));

	if(0 > iRet) // connect()실패시 음수를 반환하므로
	{
		perror("connect() ");
		close(iSock);
		return 0;
	}

	printf("\niSock = [%d] 입니다.\n\n",iSock);


	iRet = read(iSock,ucBuff,sizeof(ucBuff)); // server.c의 "WELCOME"을 읽는다.
	ucBuff[iRet] = 0; // WELCOME 다음 배열에 '0'을 넣음

	printf("[%s]\n",ucBuff);

	close(iSock);	// 소켓을 닫을때 close()사용

	return 0;
}
