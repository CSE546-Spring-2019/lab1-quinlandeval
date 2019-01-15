all: count

client: count.c
	gcc -g -o count count.c
