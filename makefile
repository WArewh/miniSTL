GPPPARAMS = -Itest -ItinySTL

SRC_TEST=$(wildcard test/*.cpp)
SRC_STL=$(wildcard tinySTL/*.cpp)

CC=g++

OBJS =$(patsubst test/%.cpp, objects/test/%.o, $(SRC_TEST)) \
	  $(patsubst tinySTL/%.cpp, objects/tinySTL/%.o, $(SRC_STL)) \
	  objects/main.o

objects/main.o:main.cpp
	mkdir -p $(@D)
	$(CC) $(GPPPARAMS) -g -c $< -o $@ 


all:$(OBJS)
	$(CC) $(GPPPARAMS) -g -o main $(OBJS)

run:all
	./main

debug:all
	cgdb main

objects/test/%.o:test/%.cpp
	mkdir -p $(@D)
	$(CC) -g $(GPPPARAMS) -o $@ -c $<

objects/tinySTL/%.o:tinySTL/%.cpp
	mkdir -p $(@D)
	$(CC) -g $(GPPPARAMS) -o $@ -c $<

clean:
	rm -rf objects main

# find . "(" -name "*.c" -or  -name "*.cpp" -or -name "*.h" ")" -print | xargs wc -l