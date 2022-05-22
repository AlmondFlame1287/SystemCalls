main:
	gcc main.c -o main -pthread -g
	gcc afterexec.c -o afterexec -pthread -g