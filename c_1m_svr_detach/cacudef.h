#ifndef __CALCUDEF__H__
#define __CALCUDEF__H__

#define SERVER_PORT		8080
#define SERVER_IP		"127.0.0.1"
#define MAX_BUFFER		128
#define MAX_EPOLLSIZE	100000
#define MAX_THREAD		80
#define MAX_PORT		100

#define CPU_CORES_SIZE	8



#define TIME_SUB_MS(tv1, tv2)  ((tv1.tv_sec - tv2.tv_sec) * 1000 + (tv1.tv_usec - tv2.tv_usec) / 1000)



#endif
