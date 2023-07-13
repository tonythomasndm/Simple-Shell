#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SIZE 1024

int isDir(char *name){
	DIR* dir = opendir(name);
	if (dir!=NULL){
		closedir(dir);	
		return 1;
	}
	return 0;
}
char **dirSeparation(char *inputStr){
    char **dir_args=(char**)malloc(sizeof(char*)*SIZE);
    char *word;
    char delim[10]="/";
    int ind=0;
    int buffer_size=SIZE;
    if(!dir_args){
        printf("Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    word=strtok(inputStr,delim);
    while(word!=NULL){
        dir_args[ind]=word;
        ind++;
        if(ind>=buffer_size){
            buffer_size+=SIZE;
            dir_args=(char**)realloc(dir_args,sizeof(char*)*buffer_size);
            if(!dir_args){
                printf("Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
        word=strtok(NULL,delim);
    }
    dir_args[ind]=NULL;
    return dir_args;
}
int main(int no_of_args,char** args)
{
	int check;
    int ind;
    if(no_of_args<2){
        printf("mkdir : Missing operands or directories not specified\n");
        return 0;
    }
    
    if(!strcmp(args[1],"-v"))
    {
        if(args[2]!=NULL)
        {   
            ind=2;
            while(args[ind]!=NULL)
            {
                check = mkdir(args[ind],0777);
                if (check)
                    printf("mkdir : Error in creating directory or directory already exists : %s\n",args[ind]);
                else
                printf("mkdir : created the directory '%s'\n",args[ind]);
                ind++;
            }
            return 0;
        }
        else
        {
            printf("mkdir : Directory name not specified\n");
            return 0;
        }
    }
    else if(!strcmp(args[1],"-m"))
    {
        if(args[3]==NULL)
        {
            printf("mkdir : Directory name not specified\n");
            return 0;
        }
        if(args[2]!=NULL)
        {
            int mode;
            char str[SIZE]="";
            int i;
            for(i=2;args[2][i]!='\0';i++)
            {
                str[i-2]=args[2][i];
            }
            str[i-2]='\0';
            sscanf(str, "%d", &mode);
            check = mkdir(args[3],mode);
            if (check)
            printf("mkdir : Error in creating directory or directory already exists : %s\n",args[ind]);
            return 1;
        }
        else
        {
            printf("mkdir : Mode not specified\n");
        }
        return 0;
    }
    else if(!strcmp(args[1],"-p"))
    {
        int k=2;
        while(args[k]!=NULL)
        {int dir_exists = isDir(args[k]);
        char* pwd_dir=getenv("PWD");
        char **dir_args;
        if(dir_exists!=1)
        {
            dir_args=dirSeparation(args[2]);
            int i=0;
            while(dir_args[i]!=NULL)
            {
                dir_exists = isDir(dir_args[i]);
                if(dir_exists)
                {
                    chdir(dir_args[i]);
                }
                else
                {
                    int ret = mkdir(dir_args[i],0777);
                    if (check)
                    printf("mkdir : Error in creating directory : %s\n",args[i]);
                    chdir(dir_args[i]);
                }
                i++;
            }
            chdir(pwd_dir);
        }
        if(args[2]==NULL)
        {
            printf("mkdir : Directory name not specified\n");
            return 0;
        }k++;
        }
    }
    else
    {
        ind=1;
        while(args[ind]!=NULL)
        {
            check = mkdir(args[ind],0777);
            if (check)
            printf("mkdir : Error in creating directory or directory already exists : %s\n",args[ind]);
            ind++;
        }
	}
    return 1;
	
}
