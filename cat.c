#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024

int main(int no_of_args, const char** args) {

    int ind,ret;
    if(no_of_args<2){
        printf("cat : Missing operands\n");
        return 0;
    }
    if(!strcmp(args[1],"-n"))
    {
        ind=2;
        int i=1;
        while(args[ind]!=NULL)
        {
            if(access(args[ind], F_OK)!=0)
            {
                printf("cat : File '%s' doesnot exist\n",args[ind]);
                ind++;
                continue;
            }
            FILE *f=fopen(args[ind],"r");
            if(f==NULL)
            {
                printf("cat : File '%s' cannot be opened \n",args[ind]);
                ind++;
                continue;
            }
            char str[SIZE];
            if(ind==2)
            {printf("0.  ");}
            while(fgets(str,SIZE,f)!=NULL){
                printf("%s",str);
                if(str[strlen(str)-1]=='\n')
                {
                    printf("%d.  ",i);
                    i++;
                }
            }
            fclose(f);
            ind++;
        }
        
    }
    else if(!strcmp(args[1],">"))
    {
        FILE *f=fopen(args[2],"w");
        fclose(f);
        return 1;
    }
    else if(!strcmp(args[2],">"))
    {
        if(no_of_args<4)
        {
             printf("cat : Missing operands\n");
            return 0;
        }
        if(access(args[1], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[1]);
                return 0;
            }
        if(access(args[3], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[3]);
                return 0;
            }
        else
        {   
            FILE *f1=fopen(args[1],"r");
            FILE *f2=fopen(args[3],"w");
            if (f1 == NULL || f2 == NULL)
            {
                printf("cat : Unable to open files\n");
                return 0;
            }
            char ch;
            ch = fgetc(f1);
            while (ch != EOF)
            {
                fputc(ch,f2);
                ch = fgetc(f1);
            }
            fclose(f1);
            fclose(f2);
            return 1;}
    }
    else if(!strcmp(args[2],">>"))
    {
        if(no_of_args<4)
        {
             printf("cat : Missing operands\n");
            return 0;
        }
        if(access(args[1], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[1]);
                return 0;
            }
        if(access(args[3], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[3]);
                return 0;
            }
        else
        {   
            FILE *f1=fopen(args[1],"r");
            FILE *f2=fopen(args[3],"a");
            if (f1 == NULL || f2 == NULL)
            {
                printf("cat : Unable to open files\n");
                return 0;
            }
            char ch;
            ch = fgetc(f1);
            while (ch != EOF)
            {
                fputc(ch,f2);
                ch = fgetc(f1);
            }
            fclose(f1);
            fclose(f2);
            return 1;}
    }
    else if(!strcmp(args[1],"-s"))
    {
        ind=2;
        while(args[ind]!=NULL)
        {
           if(access(args[ind], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[ind]);
                ind++;
                continue;
            }
            FILE *f=fopen(args[ind],"r");
            if(f==NULL)
            {
                printf("cat : File '%s' cannot be opened \n",args[ind]);
                ind++;
                continue;
            }
            char ch;
            ch=fgetc(f);
            while(ch!=EOF){
               
                if(ch==EOF)
                {
                    continue;
                }
                printf("%c",ch);
                ch=fgetc(f);
            }
            fclose(f);
            ind++;
        }
    }

    else if(!strcmp(args[1],"-E"))
    {
        ind=2;
        while(args[ind]!=NULL)
        {
           if(access(args[ind], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[ind]);
                ind++;
                continue;
            }
            FILE *f=fopen(args[ind],"r");
            if(f==NULL)
            {
                printf("cat : File '%s' cannot be opened \n",args[ind]);
                ind++;
                continue;
            }
            char ch;
            ch=fgetc(f);
            while(ch!=EOF){
                if(ch=='\n')
                {
                    printf("#");
                }
                if(ch==EOF)
                {
                    continue;
                }
                printf("%c",ch);
                ch=fgetc(f);
            }
             fclose(f);
            ind++;
        }
        
    }
    else if(!strcmp(args[1],"-k"))
    {
        ind=2;
        while(args[ind]!=NULL)
        {
           if(access(args[ind], F_OK)!=0)
            {
                printf("cat : File '%s' does not exist\n",args[ind]);
                ind++;
                continue;
            }
            FILE *f=fopen(args[ind],"r");
            if(f==NULL)
            {
                printf("cat : File '%s' cannot be opened \n",args[ind]);
                ind++;
                continue;
            }
            char ch;
            ch=fgetc(f);
            while(ch!=EOF){
                
                if(ch==EOF)
                {
                    continue;
                }
                printf("%c",ch);
                ch=fgetc(f);
            }
            fclose(f);
            ind++;
        }
    }
    
    return 1;
}