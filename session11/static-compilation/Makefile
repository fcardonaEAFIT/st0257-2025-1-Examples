
all: callmaxofthree

callmaxofthree: callmaxofthree.o maxofthree.o
	# $(CC) -static -o $@ $^
	$(CC) --verbose -o $@ $^ 

maxofthree.o: maxofthree.s
	$(AS) -o $@ -c $^

callmaxofthree.o: callmaxofthree.c
	$(CC) -c -std=c99 $<

clean:
	$(RM) -f callmaxofthree
	$(RM) -f *.o
	$(RM) -f *~ *.*~

