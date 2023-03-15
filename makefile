all:
	gcc -g -o main.o main.c os.c list.c

clean:
	rm -f ./main.o