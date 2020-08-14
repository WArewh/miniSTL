OBJS=test/simple_server test/simple_client wrap.o

wrap.o:wrap.c
	gcc -g -c wrap.c -o wrap.o

test/%:test/%.c wrap.o
	gcc -g -o $@ $< wrap.o
	./$@

clean: 
	rm -rf $(OBJS)