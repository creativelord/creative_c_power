#ifndef __IO_UTILS__H
#define __IO_UTILS__H


static int ntySetNonblock(int fd) {
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0) return flags;
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) return -1;
	return 0;
}

static int ntySetReUseAddr(int fd) {
	int reuse = 1;
	return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
}

static int ntySetAlive(int fd) {
	int alive = 1;
	int idle = 60;
	int interval = 5;
	int count = 2;

	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&alive, sizeof(alive));
	setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, (void*)&idle, sizeof(idle));
	setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, (void*)&interval, sizeof(interval));
	setsockopt(fd, SOL_TCP, TCP_KEEPCNT, (void*)&count, sizeof(count));
}


#endif

