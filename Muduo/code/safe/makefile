CC=clang++
CC_FLAGS= -Wall -g


mkdir:
	mkdir -p objects

%:%.cc mkdir
	$(CC) $(CC_FLAGS) $< -o objects/$@

clean:
	rm -rf objects
