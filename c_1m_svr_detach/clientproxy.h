#ifndef _CLIENT_OS__H__
#define _CLIENT_OS__H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/poll.h>

#include <errno.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include <pthread.h>

#include "cacudef.h"
#include "workerqueue.h"


static int curfds = 1;
static int nRun = 0;

typedef struct client {
	int fd;
	char rBuffer[MAX_BUFFER];
	int length;
} client_t;

void *client_cb(void *arg) {
	int clientfd = *(int *)arg;
	char buffer[MAX_BUFFER] = {0};

	int childpid = getpid();

	while (1) {
		bzero(buffer, MAX_BUFFER);
		ssize_t length = recv(clientfd, buffer, MAX_BUFFER, 0); //bio
		if (length > 0) {
			//printf(" PID:%d --> buffer: %s\n", childpid, buffer);

			int sLen = send(clientfd, buffer, length, 0);
			//printf(" PID:%d --> sLen: %d\n", childpid, sLen);
		} else if (length == 0) {
			printf(" PID:%d client disconnect\n", childpid);
			break;
		} else {
			printf(" PID:%d errno:%d\n", childpid, errno);
			break;
		}
	}
}
    

static int nRecv(int sockfd, void *data, size_t length, int *count) {
	int left_bytes;
	int read_bytes;
	int res;
	int ret_code;

	unsigned char *p;

	struct pollfd pollfds;
	pollfds.fd = sockfd;
	pollfds.events = ( POLLIN | POLLERR | POLLHUP );

	read_bytes = 0;
	ret_code = 0;
	p = (unsigned char *)data;
	left_bytes = length;

	while (left_bytes > 0) {

		read_bytes = recv(sockfd, p, left_bytes, 0);
		if (read_bytes > 0) {
			left_bytes -= read_bytes;
			p += read_bytes;
			continue;
 		} else if (read_bytes < 0) {
			if (!(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) {
				ret_code = (errno != 0 ? errno : EINTR);
			}
		} else {
			ret_code = ENOTCONN;
			break;
		}
		
		res = poll(&pollfds, 1, 5);
		if (pollfds.revents & POLLHUP) {
			ret_code = ENOTCONN;
			break;
		}
		if (res < 0) {
			if (errno == EINTR) {
				continue;
			}
			ret_code = (errno != 0 ? errno : EINTR);
		} else if (res == 0) {
			ret_code = ETIMEDOUT;
			break;
		}

	}

	if (count != NULL) {
		*count = length - left_bytes;
	}
	//printf("nRecv:%s, ret_code:%d, count:%d\n", (char*)data, ret_code, *count);


	return ret_code;
}

static int nSend(int sockfd, const void *buffer, int length, int flags) {

	int wrotelen = 0;
	int writeret = 0;

	unsigned char *p = (unsigned char *)buffer;

	struct pollfd pollfds = {0};
	pollfds.fd = sockfd;
	pollfds.events = ( POLLOUT | POLLERR | POLLHUP );

	do {
		int result = poll( &pollfds, 1, 5);
		if (pollfds.revents & POLLHUP) {
			
			printf(" ntySend errno:%d, revent:%x\n", errno, pollfds.revents);
			return -1;
		}

		if (result < 0) {
			if (errno == EINTR) continue;

			printf(" ntySend errno:%d, result:%d\n", errno, result);
			return -1;
		} else if (result == 0) {
		
			printf(" ntySend errno:%d, socket timeout \n", errno);
			return -1;
		}

		writeret = send( sockfd, p + wrotelen, length - wrotelen, flags );
		if( writeret <= 0 )
		{
			break;
		}
		wrotelen += writeret ;

	} while (wrotelen < length);
	
	return wrotelen;
}

void client_job(job_t *job) {
	client_t *rClient = (client_t*)job->user_data;
	int clientfd = rClient->fd;

	char buffer[MAX_BUFFER];
	bzero(buffer, MAX_BUFFER);

	int length = 0;
	int ret = nRecv(clientfd, buffer, MAX_BUFFER, &length);
	if (length > 0) {	
		if (nRun || buffer[0] == 'a') {		
			printf(" TcpRecv --> curfds : %d, buffer: %s\n", curfds, buffer);
			
			nSend(clientfd, buffer, strlen(buffer), 0);
		}

	} else if (ret == ENOTCONN) {
		curfds --;
		close(clientfd);
	} else {
		
	}

	free(rClient);
	free(job);
}

void client_data_process(int clientfd) {

	char buffer[MAX_BUFFER];
	bzero(buffer, MAX_BUFFER);
	int length = 0;
	int ret = nRecv(clientfd, buffer, MAX_BUFFER, &length);
	if (length > 0) {	
		if (nRun || buffer[0] == 'a') {		
			printf(" TcpRecv --> curfds : %d, buffer: %s\n", curfds, buffer);
			
			nSend(clientfd, buffer, strlen(buffer), 0);
		}

	} else if (ret == ENOTCONN) {
		curfds --;
		close(clientfd);
	} else {
		
	}

}




#endif 






