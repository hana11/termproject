#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>

// ----------------------------- server ------------------------------

int main(void)
{
	int iSock;
	struct sockaddr_in staddr;
	struct sockaddr_in stClient1;
	int iRet;	
	unsigned int uiSize;
	int iClient1;
	
	// IPv4를 사용하고 TCP방식 사용하는 소켓을 생성
	iSock = socket(AF_INET,SOCK_STREAM,0); 

	if(0 > iSock) // 에러발생시
	{
		perror("isock() ");
		return 0;
	}

	staddr.sin_family 	= AF_INET;
	staddr.sin_port		= htons(PORT); // '4030'번 port에 접속할 예정이다.
	staddr.sin_addr.s_addr		= inet_addr("192.168.10.250"); // 문자열(IP)를 int로 바꾸어주는 함수
	

	iRet = bind(iSock,(struct sockaddr*)&staddr,sizeof(staddr));


	if(0 > iRet) // connect()실패시 음수를 반환하므로
	{
		perror("bind() ");
		close(iSock);
		return 0;
	}

	iRet = listen(iSock,5); // 대기큐 를 5로 한정한다.

	
	if(0 > iRet) // 에러발생시
	{
		perror("listen() ");
		return 0;
	
	}
	

	
	uiSize = sizeof(staddr);
	iClient1 = accept(iSock,(struct sockaddr*)&stClient1,&uiSize); // accept();

	
	if(0 > iClient1) // accept()의 에러발생시
	{
		perror("accept() ");
		return 0;
	
	}

	
	printf("\niSock = [%d] 입니다.\n\n",iSock);
	printf("\niClient1 = [%d] 입니다.\n\n",iClient1);



	write(iClient1,"WELCOME",7); // 상대방에게 보냄


	
	close(iSock);	// 소켓을 닫을때 close()사용
	close(iClient1);
	
	return 0;
}
