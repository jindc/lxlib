/*
   @jindc
   @version 1.0
   @copy from stevens
*/

#ifndef LX_FILEIO_H
#define LX_FILEIO_H
#include <stdio.h>
#include <sys/stat.h>
#include "lx_types.h"

ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n);

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n);

ssize_t freadn(FILE* fh, void *vptr, size_t n);
ssize_t fwriten(FILE *fh, const void *vptr, size_t n);

ssize_t freadx(FILE* fh, void *vptr, size_t n,size_t x);
ssize_t fwritex(FILE *fh, const void *vptr, size_t n,size_t x);

int lx_readfile(const char * fpath, char * buff, size_t * n);
int lx_writefile(const char * fpath,lx_bool_t is_app, char * buff, size_t * n);

int lx_get_fsize(const char * path);

#endif
