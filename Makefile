all: json-test

json-test: json.c json.h  sds/sds.o
	$(CC) -o json-test json.c sds/sds.o  -Wall -std=c99 -O2

sds/sds.o: sds/sds.c sds/sds.h
	$(CC) -o sds/sds.o -c sds/sds.c  -Wall -std=c99 -O2

clean:
	rm -rf sds/sds.o json-test
