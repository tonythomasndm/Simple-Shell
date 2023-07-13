#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>

#define SIZE 1024
#define clear() printf("\033[H\033[J")

void init_shell_display(){
    clear();
    printf("***********************************************************");
    printf("***********************************************************\n\n");
    printf("\tWELCOME TO TONY'S SHELL\n\n");
    char* user_name=getenv("USER");
    printf("\n\tCurrent User: @%s\n\n",user_name);
    printf("***********************************************************");
    printf("***********************************************************\n\n\n\n");
}

void printDir(){
    char dir[SIZE];
    getcwd(dir, sizeof(dir));
    char* user_name=getenv("USER");
    printf("\033[1;32m>>%s@\033[1;34m%s \033[0m", user_name, dir);
}

int isDir(char *name){
	DIR* dir = opendir(name);
	if (dir!=NULL){
		closedir(dir);	
		return 1;
	}
	return 0;
}
int cd(int no_of_args,char **args)
{
    if(no_of_args>2){
        printf("cd : Too many operands\n");
        return 0;
    }
    if((args[1]==NULL)||(!strcmp(args[1],"--"))||(!strcmp(args[1],"~"))){
        char* home_dir=getenv("HOME");
        args[1]=home_dir;
    }
    if(!strcmp(args[1],"-")){
        args[1]="..";
    }
	int dir_exists;
	dir_exists = isDir(args[1]);		
	if (dir_exists==1){
		chdir( args[1] );                   
		return 1;                          
	}       
	printf("cd : Specified directory doesn't exist\n");
	return 0;
}
int pwd(int no_of_args,char **args)
{
    char dir[SIZE];
    getcwd(dir, sizeof(dir));
    if(no_of_args==1||(!strcmp(args[1],"-P"))||(!strcmp(args[1],"-LP")))
    {
        printf("%s\n", dir);
        return 1;
    }
    if(no_of_args>2)
    {
        printf("pwd : Too many operands\n");
        return 0;
    }
    if(!strcmp(args[1],"-v")||(!strcmp(args[1],"-vP"))||(!strcmp(args[1],"-vL"))||(!strcmp(args[1],"-vLP")))
    {
        printf("You are currently working in : %s\n",dir);
        return 1;
    }
    if(!strcmp(args[1],"-L"))
    {
        char* pwd_dir=getenv("PWD");
        printf("%s\n",pwd_dir);
        return 1;
    }
    printf("pwd : Wrong option provided for pwd command or error in command\n");
    return 0;
}
void echoBackslash(char *subStr,char *str){
    int j=0;
    for(int i=0;subStr[i]!='\0';i++)
    {
        if(subStr[i]=='\\')
        {
            i++;
            if(subStr[i]=='n')
            str[j]='\n';
            else if(subStr[i]=='t')
            str[j]='\t';
            else if(subStr[i]=='b')
            str[j]='\b';
            else if(subStr[i]=='c')
            {
                j++;
                break;
            }
            else if(subStr[i]=='r')
            str[j]='\r';
            else if(subStr[i]=='v')
            str[j]='\v';
            else if(subStr[i]=='a')
            str[j]='\a';
            else{
                str[j]='\\';
                j++;
                str[j]=subStr[i];
            }
        }
        else
        {
            str[j]=subStr[i];
        }
        j++;
    }
    str[j]='\0';
}
int echo(int no_of_args,char **args,char *line)
{
    if(no_of_args<2){
        printf("echo : Missing operands\n");
        return 0;
    }
    if((args[1][0]=='"')||(args[1][0]=='\''))
    {
        for(int i=6;line[i]!='"'&&line[i]!='\0'&&line[i]!='\'';i++){
            if(line[i]=='\n'){
                printf("\necho : Not ended with %c",line[5]);
                return 0;
            }
        }
        for(int i=6;line[i]!='"'&&line[i]!='\0'&&line[i]!='\'';i++){

            printf("%c",line[i]);
        }
        printf("\n");
        return 1;
    }
    if(!(strcmp(args[1],"-e")))
    {
        char subStr[SIZE];
        int i,j=0;
        for(i=9;line[i]!='"'&&line[i]!='\0'&&line[i]!='\'';i++){
            subStr[j]=line[i];
            j++;
        }
        subStr[j]='\0';
        char str[SIZE];
        echoBackslash(subStr,str);
        printf("%s\n",str);
        return 1;
    }
    if(!(strcmp(args[1],"-n"))||(!strcmp(args[1],"-en"))||(!strcmp(args[1],"-ne")))
    {
        for(int i=9;line[i]!='"'&&line[i]!='\0'&&line[i]!='\'';i++){
            if(line[i]=='\n'){
                printf("\necho : Not ended with %c\n",line[8]);
                break;
            }
            printf("%c",line[i]);
        }
        return 1;
    }
    if(!(strcmp(args[1],"$PWD")))
    {
        char pwd[SIZE];
        getcwd(pwd, sizeof(pwd));
        printf("%s\n", pwd);
        return 1;
    }
    // if(!(strcmp(args[1],"*")))
    // {

    // }
    printf("echo : Wrong options given or incorrectly command given\n");
    return 0;
}
int argumentCount(char **args){
    int ind=0;
    while(args[ind]!=NULL){
        ind++;
    }
    return ind;
}

int getInput(char* inputStr)
{
    char str[SIZE];
	printf(" >> ");
    fgets(str,SIZE,stdin);
    if (strlen(str) != 0) {
        strcpy(inputStr, str);
        return 0;
    } else {
        return 1;
    }
}
char **argumentSeparation(char *inputStr){
    char **com_args=(char**)malloc(sizeof(char*)*SIZE);
    char *word;
    char delim[10]=" \t\n\r\a";
    int ind=0;
    int buffer_size=SIZE;
    if(!com_args){
        printf("Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    word=strtok(inputStr,delim);
    while(word!=NULL){
        com_args[ind]=word;
        ind++;
        if(ind>=buffer_size){
            buffer_size+=SIZE;
            com_args=(char**)realloc(com_args,sizeof(char*)*buffer_size);
            if(!com_args){
                printf("Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
        word=strtok(NULL,delim);
    }
    com_args[ind]=NULL;
    return com_args;
}
void* exfunc(void *arg)
{
    char **args=(char**)arg;
    pthread_detach(pthread_self());
    char comfile[SIZE];
    if(!(strcmp(args[0], "ls")))
        strcpy(comfile, "./ls");
    else if(!(strcmp(args[0],"cat")))
        strcpy(comfile, "./cat");
    else if(!(strcmp(args[0], "date")))
        strcpy(comfile, "./date");
    else if(!(strcmp(args[0],"rm")))
        strcpy(comfile,"./rm");
    else if(!(strcmp(args[0],"mkdir")))
        strcpy(comfile,"./mkdir");
    else
    {
        printf("Command Error -Thread Version : Command not found!!\n");
        printf("Please enter one of the following command : cd, pwd, echo, ls, cat, date, rm and mkdir\n");
        pthread_exit(NULL);
    }
    int ind=1;
    while(args[ind]!=NULL)
    {
        strcat(comfile," ");
        strcat(comfile,args[ind]);
        ind++;
    }
    int ret=system(comfile);
    if(ret==-1)
    {
        printf("Error in system call() : Child process could not be created or its status could not be retrived\n");
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){

	char line1[SIZE];
	char **args;
    char *line2;
	int flag=1;
    int no_of_args;

    init_shell_display();

	while(flag){
		printDir();
		if (getInput(line1))
            continue;
        line2=strdup(line1);
        args=argumentSeparation(line1);
		no_of_args=argumentCount(args);
        if(!strcmp(args[0],"cd")){
            cd(no_of_args,args);
            continue;
        }
        else if(!strcmp(args[0],"pwd")){
            pwd(no_of_args,args);
            continue;
        }
        else if(!strcmp(args[0],"echo")){
            echo(no_of_args,args,line2);
            continue;
        }
        else if(!strcmp(args[0],"exit")){
            printf("Thank you for using my shell.......\nexiting\n");
            exit(0);
        }
        
        //ls,cat,date,rm,mkdir
        if((strcmp(args[1],"&t")))
        {
            pid_t pid,wpid;
            pid =fork();
            if(pid<0){
                printf("Error in fork() : Could not create a child process\n");
            }

            else if(pid == 0)
            {
                char comfile[SIZE];
                
                if(!(strcmp(args[0], "ls")))
                    strcpy(comfile, "./ls");
                else if(!(strcmp(args[0],"cat")))
                    strcpy(comfile, "./cat");
                else if(!(strcmp(args[0], "date")))
                    strcpy(comfile, "./date");
                else if(!(strcmp(args[0],"rm")))
                    strcpy(comfile,"./rm");
                else if(!(strcmp(args[0],"mkdir")))
                    strcpy(comfile,"./mkdir");
                else
                {
                    printf("Command Error : Command not found!!\n");
                    printf("Please enter one of the following command : cd, pwd, echo, ls, cat, date, rm and mkdir\n");
                    continue;
                }
                if (execv(comfile, args) < 0)
                {
                    printf("Error in execv()\n");
                }
            }
            else if(pid >0)
            {
                wpid=waitpid(pid,NULL, WUNTRACED);
                if(wpid<0)
                {
                    printf("Error in waitpid() : Process not terminated");
                }
            }
        }
        else
        {
            char comm[SIZE]="";
            strcat(comm,args[0]);
            if(args[2]!=NULL)
            {
                strcat(comm," ");
                strcat(comm,args[2]);
                int ind=3;
                while(args[ind]!=NULL)
                {
                    strcat(comm," ");
                    strcat(comm,args[ind]);
                    ind++;
                }
            }
            args=argumentSeparation(comm);
		    no_of_args=argumentCount(args);

            pthread_t ptid;
            int ret=pthread_create(&ptid,NULL,&exfunc,args);
            if(ret){
                printf("Error in pthread_create(): Thread not created\n");
                continue;
            }
            if(pthread_equal(ptid,pthread_self()))
            {
                printf("Error in pthread_create() : Same thread running");
            }
            pthread_join(ptid,NULL);
        }
	}
    return 0;
}
