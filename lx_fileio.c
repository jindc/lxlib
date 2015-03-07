#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "lx_fileio.h"

ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return n - nleft;
}
/* end writen */

ssize_t freadn(FILE* fh, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = fread(ptr, 1, nleft, fh)) <= 0) {
			if ( !ferror(fh))
				break;		/*  */
			else
				return(-1);
		} 

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}

ssize_t freadx(FILE* fh, void *vptr, size_t n,size_t x)
{
	size_t num = x < n ? x:n;
	return freadn(fh,vptr,num);
}


ssize_t fwriten(FILE *fh, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = fwrite(ptr,1, nleft,fh)) <= 0) {
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return n - nleft;
}

ssize_t fwritex(FILE *fh, const void *vptr, size_t n,size_t x)
{
	size_t num = x < n?x :n;
	return fwriten(fh,vptr,num);
}

int lx_readfile(const char * fpath, char * buff, size_t * n)
{
    FILE * fh;
    int ret;
    
    if( (fh = fopen(fpath,"rb") ) == NULL)
        return -1;    
    
    ret = freadn(fh,buff,*n);
    if(ret < 0){
        fclose(fh);
        return -1;
    }

    *n = ret;
    fclose(fh);
    return 0;
}

int lx_writefile(const char * fpath,lx_bool_t is_app, char * buff, size_t * n)
{
    FILE * fh;
    int ret;
    char * mode;
    
    mode = is_app?"ab":"wb";
    if( (fh = fopen(fpath,mode) ) == NULL)
        return -1;    
    
    ret =fwriten(fh,buff,*n);
    if(ret < 0){
        fclose(fh);
        return -1;
    }

    *n = ret;
    fclose(fh);
    return 0;
}


int lx_get_fsize(const char * path)
{
    int fsize = -1;
    struct stat statb;
    if( stat(path,&statb)==0 && S_ISREG(statb.st_mode)){
       fsize = (int)statb.st_size;     
    }
    return fsize;
}




/* end writen */
