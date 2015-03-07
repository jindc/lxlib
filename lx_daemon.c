#include "lx_daemon.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "lx_signal.h"

int lx_daemon()
{
    pid_t pid;

    if( (pid = fork()) < 0)
        return -1;
    else if(pid > 0)
        exit(EXIT_SUCCESS);
    
   if(setsid() < 0)
       return -1;
   if(lx_signal(SIGHUP,SIG_IGN ) == SIG_ERR )
       return -1;

   if( (pid = fork() ) < 0)
       return -1;
   else if(pid)
       exit(EXIT_SUCCESS);

   return 0;

}
