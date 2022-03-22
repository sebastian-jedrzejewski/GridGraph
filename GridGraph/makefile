all: main.o
	cc -o gridgraph main.o read.o write.o graph.o helpers.o

main.o: main.c read.o write.o graph.o helpers.o

read.o: read.c graph.o

write.o: write.c graph.o helpers.o

graph.o: graph.c

helpers.o: helpers.c

clean:
	rm gridgraph *.o

test:
	./gridgraph -w -xh 6 -xw 6 -Wmin 0.5 -Wmax 0.9 -Cmin 1 -Cmax 3