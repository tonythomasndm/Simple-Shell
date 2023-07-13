#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 1024

int main(int no_of_args,char** args)
{
    if(no_of_args>2)
    {
        printf("date : Too many operands");
        return 0;
    }
    if(no_of_args==2&&(!strcmp(args[1],"-n")))
    {
        time_t t;   
        time(&t);
        printf("%s", ctime(&t));
        return 0;
    }
    char buf[SIZE];
    char buf1[SIZE];
    char buf2[SIZE];
    struct tm *timeT;
    time_t t= time(NULL);
    if(t==-1)
    {
        printf("date : time() fails");
    }
    timeT=localtime(&t);
    if(timeT==NULL)
    {
        printf("date : localtime() fails");
    }
    strftime(buf1,SIZE,"%a", timeT);
	strftime(buf2,SIZE,"%b", timeT);
    if (!strcmp(args[1], "-u"))
    {
        timeT=gmtime(&t);
        printf("%s %s %02d %02d:%02d:%02d UTC %d \n",buf1,buf2,timeT->tm_mday ,timeT->tm_hour, timeT->tm_min, timeT->tm_sec, timeT->tm_year+1900);
    }
    else if(strcmp(args[1], "-r"))
    {   strftime(buf, SIZE,"%z",timeT);
        printf("%s, %02d %s %d %02d:%02d:%02d %s \n",buf1,timeT->tm_mday,buf2 ,timeT->tm_year+1900,timeT->tm_hour, timeT->tm_min, timeT->tm_sec, buf);
    }
    else
    {   strftime(buf, SIZE,"%Z",timeT);
        printf("%s %s %02d %02d:%02d:%02d %s %d \n",buf1,buf2,timeT->tm_mday ,timeT->tm_hour, timeT->tm_min, timeT->tm_sec,buf, timeT->tm_year+1900);
    }
    memset(buf, 0, SIZE);
    memset(buf1, 0, SIZE);
    memset(buf2, 0, SIZE);
    
    return 0;
}