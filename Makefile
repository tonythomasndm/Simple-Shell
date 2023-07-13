default:
	gcc cat.c -o cat
	gcc rm.c -o rm
	gcc date.c -o date
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc -pthread -o shell shell.c && ./shell
clear:
	rm -rf shell cat rm date ls mkdir