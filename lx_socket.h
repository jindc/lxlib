#ifndef LX_SOCKET_H
#define LX_SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>

struct lx_connection
{
    int fd;
    struct sockaddr_in addr;
    struct timeval accept_time;
};
typedef struct lx_connection lx_connection;

int lx_block_sigpipe();

int lx_set_nonblocking( int fd);

int lx_set_timeo(int fd,int s_milli,int r_milli);

int lx_sorecv(int fd,char * buff,size_t n);

int lx_sosend(int fd, char* buff, size_t n);

int lx_listen(short port);

//-1 and error on errno
int lx_start_server(int listen_fd,int (handler)(void *), void * arg);

#endif


