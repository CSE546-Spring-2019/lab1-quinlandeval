all: count

client: count.c
	gcc -g -Wall -o count count.c
