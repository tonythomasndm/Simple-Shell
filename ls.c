#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define SIZE 1024

int main(int no_of_args,char** args) {
	int count_a = 0;
	int count_A = 0;
	DIR *dir;
    if(!strcmp(args[1],"-n"))
    {
        args[1]=NULL;
        no_of_args-=1;
    }
	for (int i= 0; i < no_of_args;i++)
	{
		if (!strcmp(args[i], "-A"))
			count_A = 1;
		if (!strcmp(args[i], "-a"))
			count_a = 1;
	}
	if (count_a + count_A + 1 == no_of_args)
	{
		args[1] = (char *)malloc(2 * sizeof(char));
		args[1][0] = '.';
		args[1][1] = '\0';
	}
	if (no_of_args == 1)
		no_of_args = 2;
	for (int i = 1; i < no_of_args; i++)
	{
		if ((!(strcmp(args[i], "-A")))||(!(strcmp(args[i], "-a"))))
			continue;
		dir = opendir(args[i]);
		if (dir == NULL)
		{
			printf("ls : Directory does not exists\n");
			return 0;
		}
		struct dirent *f;
		f = readdir(dir);
		if (f == NULL)
			printf("ls : Directory does not exists\n");
		if (count_A + count_a + 2 != no_of_args)
			printf("%s : \n ", args[i]);
		while (f != NULL)
		{
			char tmp[SIZE];
			if (f->d_name[0] == '.')
			{
				if (count_a)
					printf("%s ", f->d_name);
				else if (count_A && strcmp(f->d_name, ".") && strcmp(f->d_name, ".."))
					printf("%s ", f->d_name);
			}
			else
				printf("%s ", f->d_name);
			f = readdir(dir);
		}
		printf("\n");
	}
    return 0;
}