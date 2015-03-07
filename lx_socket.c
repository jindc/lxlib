#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "lx_socket.h"

int lx_block_sigpipe()
{
   int ret;
   
   sigset_t set;
   sigemptyset(&set);
   sigaddset(&set,SIGPIPE);

   if( ( ret = pthread_sigmask(SIG_BLOCK,&set,NULL)) != 0)
   {
        errno = ret;
        return -1;
   }

   return 0;
}

int lx_listen( short port)
{
    const int on = 1;
    int listen_fd = -1;
    struct sockaddr_in addr;
    if(lx_block_sigpipe())
        goto err;

    listen_fd = socket(PF_INET,SOCK_STREAM,0);
    if(listen_fd == -1)
        goto err;

    if(setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))
        goto err;

    memset(&addr,0,sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listen_fd,(struct sockaddr *)&addr,sizeof(addr)))
        goto err;

    if(listen(listen_fd,SOMAXCONN))
        goto err;

    return listen_fd;

err:
    if(listen_fd >=  0)
        close(listen_fd);
    return -1;
}

int lx_set_nonblocking( int fd)
{
    int flags,ret = 0;

    while( (flags = fcntl(fd,F_GETFL,0)) == -1  ||
            (ret = fcntl(fd,F_SETFL,flags | O_NONBLOCK )) != 0  ){
        if(errno == EAGAIN || errno == EINTR || errno == EACCES)
            continue;
        else{
            ret = -1;
            goto end;
        }
    }

end:
    return ret;
}

int lx_set_timeo(int fd,int s_milli,int r_milli)
{
    int ret,i;
    struct timeval tv;

    int names[] = {SO_SNDTIMEO,SO_RCVTIMEO};
    int values[] ={s_milli,r_milli};

    for(i=0;i <2;++i)
    {
        if(values[i] >=0){
            tv.tv_sec = values[i]/1000;
            tv.tv_usec = (values[i]%1000)*1000;
            if(setsockopt(fd,SOL_SOCKET, names[i],&tv,sizeof(tv)))
                return -1;
        }
    }
    return 0;
}

int lx_start_server(int listen_fd,int (handler)(void *), void * arg)
{
    struct sockaddr_in peer_addr;
    int peer_fd;
    int addrlen;
    lx_connection* conn = (lx_connection *)arg;
    addrlen = sizeof(peer_addr);

    while(1)
    {
        peer_fd = accept(listen_fd,(struct sockaddr *)&peer_addr, &addrlen);
        if(peer_fd < 0)
            return -1;

        conn->fd = peer_fd;
        conn->addr = peer_addr;
        gettimeofday( &(conn->accept_time),NULL);
        if( handler( arg)  )
            break;
    }

    if(listen_fd >= 0)
        close(listen_fd);
    return 0;
}

int lx_sorecv(int fd,char * buff,size_t n)
{
    int left,has;
    int ret;
    
    left = n;
    has = 0;
    while(left > 0 ){
        ret = recv(fd,buff + has,left,0);
        if( ret == 0)
            break;

        if( ret < 0)
        {
            if(errno == EINTR ){
                ret = 0;
            }else
                return -1;
        }

        has += ret;
        left -=ret;
   }

   return has;
}

int lx_sosend(int fd, char* buff, size_t n)
{
    int left,has,ret;
    
    has = 0;
    left = n;
    while(left >0){
        ret = send(fd,buff+has,left,0);
        
        if(ret <=0){
            if(errno == EINTR)
                ret = 0;
            else
                return -1;
        }
        
        left -= ret;
        has += ret;
   }

   return has;
}
