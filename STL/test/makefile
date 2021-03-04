GPPPARAMS = -I../tinySTL -Wall

SRC_TEST=$(wildcard src/*.cc)
SRC_STL=$(wildcard ../tinySTL/*.cc)

CC=clang++

OBJS =$(patsubst src/%.cc, objects/test/%.o, $(SRC_TEST)) \
	  $(patsubst ../tinySTL/%.cc, objects/tinySTL/%.o, $(SRC_STL)) \

all:$(OBJS)
	$(CC) $(GPPPARAMS) -g -o main $(OBJS)

run:all
	./main

debug:all
	cgdb main

objects/test/%.o:src/%.cc
	mkdir -p $(@D)
	$(CC) -g $(GPPPARAMS) -o $@ -c $<

objects/tinySTL/%.o:../tinySTL/%.cc
	mkdir -p $(@D)
	$(CC) -g $(GPPPARAMS) -o $@ -c $<

clean:
	rm -rf objects main

# find . "(" -name "*.cc" -or -name "*.h" ")" -print | xargs wc -l
