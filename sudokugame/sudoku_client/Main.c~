#include "Sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc, char *argv[])
{
	int select_;
	int serv_sock;
	int clnt_sock;
	int n;
	fd_set reads;
	int maxfd;
	int level=0;
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;
	char message[BUF_SIZE];
	int str_len, i;
	int start_flag=0;
	if (argc != 3)
	{
		printf("Usage:%s<port>\n", argv[0]);
		exit(1);
	}
	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (clnt_sock == -1)
		error_handling("socket() error");
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));
	if (connect(clnt_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");
	else
		puts("Connected.......");
	printf("Select Sudoku- Easy : 1,2  Medium : 3,4  Hard : 5,6  Stop : 999 \n");
	while (1)
	{
		maxfd=clnt_sock+1;
		FD_ZERO(&reads);
		FD_SET(0, &reads);
		FD_SET(clnt_sock, &reads);
		select_ = select(maxfd, &reads, NULL, NULL, NULL);

		if (FD_ISSET(0, &reads))
		{
			n = read(0, message, BUF_SIZE);
			if (n>0)
			{
				if (write(clnt_sock, message, n) != n)
				error_handling("fail in sending");
			}
		}
		if (FD_ISSET(clnt_sock, &reads))
		{
			n = read(clnt_sock, message, sizeof(message));
			if (n!=0)
			{
			message[n] = '\0';
			printf("receive : %s", message);
			level = message[0]-48;
			if(strstr(message,"start"))
			{
				start_flag =1;
			}

			if(level>0 && level<7 && start_flag==1)
			{

				start_sudoku(level);

				write(clnt_sock, "finish", n);
			}
			//close(clnt_sock);
			}
		}
	}
	close(clnt_sock);
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
