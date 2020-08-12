OBJS=pipe fifo myfifo mmap sigchld
TXT=test_mmap.txt

%:%.c
	gcc -g -o $@ $< -I../
	./$@

clean: 
	rm -rf $(OBJS) $(TXT)