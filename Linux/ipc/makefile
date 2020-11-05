OBJS=pipe fifo myfifo mmap sigchld
TXT=test_mmap.txt

%:%.c
	gcc -g -o $@ $<
	./$@

clean: 
	rm -rf $(OBJS) $(TXT)