SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc,objects/%.o,$(SRC))

run:all
	./main


all:mkdir_obj $(OBJ)
	g++ -g $(OBJ) -o main

debug:all
	cgdb main


mkdir_obj:
	mkdir -p objects

objects/%.o:%.cc
	g++ -g -c $< -o $@

disk_clear:
	dd if=/dev/zero of=disk bs=512 count=16384

clean:
	rm -rf main objects