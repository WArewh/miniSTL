OBJS=test/simple_server \
	 test/simple_client \
	 test/mps.o test/mps \
	 test/mts.o test/mts \
	 test/ms.o test/ms \
	 wrap.o

wrap.o:wrap.c
	gcc -g -c wrap.c -o $@

mts.o:test/multi_pthread_server.c
	gcc -g -c $< -o test/mts.o

mts:mts.o wrap.o
	gcc -o test/mts test/mts.o wrap.o -lpthread 
	./test/mts

mps.o:test/multi_process_server.c
	gcc -g -c $< -o test/mps.o

mps:mps.o wrap.o
	gcc -o test/mps test/mps.o wrap.o
	./test/mps

ms.o:test/multiplexer_server.c
	gcc -g -c $< -o test/ms.o

ms:ms.o wrap.o
	gcc -o test/ms test/ms.o wrap.o
	./test/ms

clean: 
	rm -rf $(OBJS)