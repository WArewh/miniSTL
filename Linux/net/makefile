OBJS=test/simple_server \
	 test/simple_client \
	 test/mps.o test/mps \
	 test/mts.o test/mts \
	 test/ss.o test/ss \
	 test/es1.o test/es1 \
	 test/es2.o test/es2 \
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

es1.o:test/epoll_server1.c
	gcc -g -c $< -o test/es1.o

es1:es1.o wrap.o
	gcc -o test/es1 test/es1.o wrap.o
	./test/es1

es2.o:test/epoll_server2.c
	gcc -g -c $< -o test/es2.o

es2:es2.o wrap.o
	gcc -o test/es2 test/es2.o wrap.o
	./test/es2

clean: 
	rm -rf $(OBJS)