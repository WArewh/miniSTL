OBJS=test/simple_server \
	 test/simple_client \
	 test/mps.o test/mps \
	 test/mts.o test/mts \
	 test/ss.o test/ss \
	 test/es.o test/es \
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

ss.o:test/select_server.c
	gcc -g -c $< -o test/ss.o

ss:ss.o wrap.o
	gcc -o test/ss test/ss.o wrap.o
	./test/ss

es.o:test/epoll_server.c
	gcc -g -c $< -o test/es.o

es:es.o wrap.o
	gcc -o test/es test/es.o wrap.o
	./test/es

clean: 
	rm -rf $(OBJS)