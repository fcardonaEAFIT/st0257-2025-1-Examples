TARGETS = read createDirect readDirect writeDirect

all: ${TARGETS}

readDirect: readDirect.o record.o

writeDirect: writeDirect.o record.o

record.o: record.c record.h

readDirect.o: readDirect.c record.h

writeDirect.o: writeDirect.c

clean:
	rm -f ${TARGETS}
	rm -f *.o
	rm -f *.*~ *~
