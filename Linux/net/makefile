OBJS=tcp_server tcp_client

%:%.c
	gcc -g -o $@ $<
	./$@

clean: 
	rm -rf $(OBJS)