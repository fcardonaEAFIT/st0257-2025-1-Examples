all: threads

threads: threads.o
	$(CC) -o $@ threads.o -lpthread

threads.o: threads.c
	$(CC) -c $<

clean:
	rm *.o
	rm -f *.*~ *~
