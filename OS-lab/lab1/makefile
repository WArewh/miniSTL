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

clean:
	rm -rf main objects