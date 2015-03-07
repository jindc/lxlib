#ifndef LXFLOCK_H
#define LXFLOCK_H

#include <unistd.h>
#include <fcntl.h>

static int lx_flockcore(int fd, int cmd, short type,short whence, off_t start ,off_t len)
{
    struct flock fl;
    
    fl.l_type = type;

    fl.l_whence = whence;
    fl.l_start = start;
    fl.l_len = len;

    return fcntl(fd,cmd,&fl);
}

#define lx_lread(fd,whence,start,len) \
    lx_flockcore(fd,F_SETLK,F_RDLCK,whence,start,len)
#define lx_lreadw(fd,whence,start,len) \
    lx_flockcore(fd,F_SETLKW,F_RDLCK,whence,start,len)

#define lx_lwrite(fd,whence,start,len) \
    lx_flockcore(fd,F_SETLK,F_WRLCK,whence,start,len)
#define lx_lwritew(fd,whence,start,len) \
    lx_flockcore(fd,F_SETLKW,F_WRLCK,whence,start,len)

#define lx_lunlock(fd,whence,start,len) \
    lx_flockcore(fd,F_SETLK,F_UNLCK, whence, start,len)













#endif
