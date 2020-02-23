CC=gcc
WARN=-Wall
GTKLIB=`pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -rdynamic



build: array_op.o dir.o main.o querry.o queue.o stack.o structs.o
	$(CC) array_op.o dir.o main.o querry.o queue.o stack.o structs.o -o search_engine $(WARN) $(GTKLIB)

array_op.o: array_op.c
	$(CC) array_op.c -c $(WARN) $(GTKLIB)

dir.o: dir.c
	$(CC) dir.c -c $(WARN) $(GTKLIB)

main.o: main.c
	$(CC) main.c -c $(WARN) $(GTKLIB)

querry.o: querry.c
	$(CC) querry.c -c $(WARN) $(GTKLIB)

queue.o: queue.c
	$(CC) queue.c -c $(WARN) $(GTKLIB)

stack.o: stack.c
	$(CC) stack.c -c $(WARN) $(GTKLIB)

structs.o: structs.c
	$(CC) structs.c -c $(WARN) $(GTKLIB)

clean:
	rm -rf *.o 
	rm -rf search_engine

run:
	./search_engine

.PHONY: clean
