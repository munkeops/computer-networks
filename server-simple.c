#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<time.h>
#define MAXLINE 10000
#define LISTENQ 5

typedef const struct sockaddr SA;

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	/* change this*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =htonl(INADDR_ANY);	 
	servaddr.sin_port = htons(5500); /* change this */
   SA cliaddr;
 

	/* change this to regular call*/
	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	/* change this*/
	listen(listenfd, LISTENQ);

printf("Local IP address : %s \n", inet_ntoa(servaddr.sin_addr));

	for (;;)
	{
		connfd = accept(listenfd, (SA *)&cliaddr, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		/*change this */

		write(connfd, buff, strlen(buff));

		close(connfd);
	}
}
