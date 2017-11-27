#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    int fd;
    char *data;
    struct stat sbuf;
    int count[256]={0};

    if((fd=open("ANNA_KARENINA.txt", O_RDONLY))==-1){
        perror("open");
        exit(1);
    }

    if(stat("ANNA_KARENINA.txt",&sbuf) == -1){
        perror("stat");
        exit(1);
    }

    if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)){
        perror("mmap");
        exit(1);
    }

    for(int i = 0;i<sbuf.st_size;i++){
        count[data[i]]++;
    }
    for(int k = 0;k<256;k++){
        if(count[k]>0){
            printf("char %c : %d times\n",k, count[k]);
        }
    }
    return 0;
}
