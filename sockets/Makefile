#links objects files -- all of them are executed
all:
	gcc head.o -o head -std=c99; gcc node.o -o node -std=c99


head: head.o 
	gcc head.o -o head -std=c99

node: node.o
	gcc node.o -o node -std=c99

node.o: node.h
	gcc -c node.c -o node.o -std=c99

head.o: head.h
	gcc -c head.c -o head.o -std=c99

clean:
	rm ./head ./node; rm ./*.o
