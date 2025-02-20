all: threads

threads: threads.obj
	$(CC) /Fe:threads threads.obj

threads.obj: threads.c
	$(CC) /c threads.c

