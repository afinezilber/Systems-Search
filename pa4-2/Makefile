CFLAGS = -Wall -g

all: search index

search: stokenizer.o search.o main.o
	gcc $(CFLAGS) stokenizer.o search.o main.o -lreadline -o search

stokenizer.o: stokenizer.c
	gcc $(CFLAGS) -c stokenizer.c -o stokenizer.o

search.o: search.c
	gcc $(CFLAGS) -c search.c -o search.o
	
main.o: main.c
	gcc $(GFLAGS) -c main.c -o main.o 
	
index: tokens.o traverse.o index.o indmain.o
	gcc $(CFLAGS) tokens.o traverse.o index.o indmain.o -o index

tokens.o: tokens.c
	gcc $(CFLAGS) -c tokens.c -o tokens.o

traverse.o: traverse.c
	gcc $(CFLAGS) -c traverse.c -o traverse.o

index.o: index.c
	gcc $(CFLAGS) -c index.c -o index.o

indmain.o: indmain.c
	gcc $(GFLAGS) -c indmain.c -o indmain.o	

clean:
	rm -f search
	rm -f index
	rm -f *.o
