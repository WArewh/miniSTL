OBJS=file/file1 file/file2 file/file3 file/file4 \
	 std/std1 std/std2 \
	 
TXT=file/2.txt file/test.txt \
	 std/1.txt std/2.txt std/data \
	 adv/test.txt adv/test1.txt adv/test2.txt adv/test3.txt

file/%:file/%.c
	gcc -g -o $@ $< 

file1:file/file1
	file/file1

file2:file/file2
	file/file2

file3:file/file3
	file/file3


std/%:std/%.c
	gcc -g -o $@ $<

std1:std/std1
	std/std1

std2:std/std2
	std/std2

clean:
	rm -rf $(OBJS) $(TXT)