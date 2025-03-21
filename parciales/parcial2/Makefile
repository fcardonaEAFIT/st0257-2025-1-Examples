all: problem1 problem2

problem1: problem1.o
	$(CC) -o $@ $<

problem1.o: problem1.c
	$(CC) -c $^

problem2: problem2.o
	$(CC) -o $@ $<

problem2.o: problem2.c
	CFLAGS="-Wno-pointer-to-int-cast -Wno-int-to-pointer-cast"
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.*~ *~
	rm -f *.o
	rm -f problem1 problem2


