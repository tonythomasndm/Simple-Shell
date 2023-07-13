#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define SIZE 1024

int main(int no_of_args,char** args)
{
    int ind,ret;
    if(no_of_args<2){
        printf("rm : Missing operands\n");
        return 0;
    }
    else if(!strcmp(args[1],"-i"))
    {
        ind=2;
        char ans[SIZE];
        while(args[ind]!=NULL)
        {
            printf("rm : Are you sure you want to remnove this file '%s' : ",args[ind]);
            scanf("%s",ans);
            if((!strcmp(ans,"Y"))||(!strcmp(ans,"y"))||(!strcmp(ans,"YES"))||(!strcmp(ans,"Yes"))||(!strcmp(ans,"yes"))){    
                ret =remove(args[ind]);
                if(ret){
                    printf("rm : Error in deleting file '%s'\n",args[ind]);
                }
            }
            ind++;
        }
    }
    else if(!strcmp(args[1],"-v"))
    {
        ind=2;
        while(args[ind]!=NULL)
        {
                ret =remove(args[ind]);
                if(ret)
                    printf("rm : Error in deleting file '%s'\n",args[ind]);
                else
                {
                    printf("rm : deleted the file '%s'\n",args[ind]);
                }
            
            ind++;
        }
    }
    else if((!strcmp(args[1],"-r"))||(!strcmp(args[1],"-f")))
    {
        ind=2;
        char cmd[SIZE]="";
        while(args[ind]!=NULL)
        {
            ret =remove(args[ind]);
            if(ret)
            {
                    strcat(cmd,"rm -rf ");
                    strcat(cmd,args[ind]);
                    ret=system(cmd);
                    if(ret!=0)
                    printf("rm : Error in removing the file or empty directory\n");
            }
        }
    }
    else
    {
        ind=1;
        while(args[ind]!=NULL)
        {
            ret =remove(args[ind]);
            if(ret){
                printf("rm : Error in deleting file '%s'\n",args[ind]);
            }
            ind++;
        }
    }
    return 1;
}