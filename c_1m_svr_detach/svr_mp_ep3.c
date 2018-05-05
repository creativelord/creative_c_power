#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/poll.h>

#include <errno.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#include "cacudef.h"

#include "clientproxy.h"
#include "ioutils.h"
#include "workerqueue.h"


int svrsockfds[MAX_PORT] = {0};

//判断服务器段socket fd
int isSvrListenfd(int fd, int *fds) {
	int i = 0;

	for (i = 0;i < MAX_PORT;i ++) {
		if (fd == *(fds+i)) return *(fds+i); //存在就返回自身 否则查找失败
	}
	return 0;
}

void *listen_thread(void *arg) {

	int i = 0;
	int epoll_fd = *(int *)arg;
	struct epoll_event events[MAX_EPOLLSIZE];

	while (1) {

		int nfds = epoll_wait(epoll_fd, events, curfds, 5);  
		if (nfds == -1) {
			perror("epoll_wait");
			break;
		}
		for (i = 0;i < nfds;i ++) {

            //就是判断 sockfd 是不是server fd
			int sockfd = isSvrListenfd(events[i].data.fd, svrsockfds);
			if (sockfd) {
				struct sockaddr_in client_addr;
				memset(&client_addr, 0, sizeof(struct sockaddr_in));
				socklen_t client_len = sizeof(client_addr);
				
				int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
				if (clientfd < 0) {
					perror("accept");
					return NULL;
				}
				
				if (curfds ++ > 1000 * 1000) {
					nRun = 1;
				}

				if (curfds % 1000 == 999) {
					
					printf("connections: %d, sockfd:%d\n", curfds, clientfd);
				}
 
				ntySetNonblock(clientfd);
				ntySetReUseAddr(clientfd);

				struct epoll_event ev;
				ev.events = EPOLLIN | EPOLLET | EPOLLOUT;
				ev.data.fd = clientfd;
				epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientfd, &ev);

			} else {

				int clientfd = events[i].data.fd;
 
				if (nRun) {
					printf(" New Data is Comming\n");
					client_data_process(clientfd);
				} else {
			
					client_t *rClient = (client_t*)malloc(sizeof(client_t));
					memset(rClient, 0, sizeof(client_t));				
					rClient->fd = clientfd;
					
					job_t *job = malloc(sizeof(job_t));
					job->job_function = client_job;
					job->user_data = rClient;
					workqueue_add_job(&workqueue, job);
					
					
				}
 
			}
		}
		
	}
	
}

int main(void) {
	
	int i = 0;
	threadpool_init(); //
	int epoll_fds[CPU_CORES_SIZE] = {0};
	pthread_t thread_id[CPU_CORES_SIZE] = {0};

	for (i = 0;i < CPU_CORES_SIZE;i ++) {
		epoll_fds[i] = epoll_create(MAX_EPOLLSIZE);

		pthread_create(&thread_id[i], NULL, listen_thread, &epoll_fds[i]);
	}
 
	for (i = 0;i < MAX_PORT;i ++) {

		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) {
			perror("socket");
			return 1;
		}

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(struct sockaddr_in));
		
		addr.sin_family = AF_INET;
		addr.sin_port = htons(SERVER_PORT+i);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
			perror("bind");
			return 2;
		}
        //存储sever listener socket 后面需要作为判断的
		svrsockfds[i] = sockfd;
		

		struct epoll_event ev;
		 
		ev.events = EPOLLIN | EPOLLET; //EPOLLLT
		ev.data.fd = sockfd;
		epoll_ctl(epoll_fds[i%CPU_CORES_SIZE], EPOLL_CTL_ADD, sockfd, &ev);  

		if (listen(sockfd, 5) < 0) {
			perror("listen");
			return 3;
		}
		printf("C1000K Server Listen on Port:%d\n", SERVER_PORT+i);
		
	}

	for (i = 0;i < CPU_CORES_SIZE;i ++) {
		pthread_join(thread_id[i], NULL);
	}


	getchar();
	printf("end\n");
}






