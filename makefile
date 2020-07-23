GPPPARAMS = -Iinclude -ItinySTL

SRC_TEST=$(wildcard test/*.cpp)
SRC_STL=$(wildcard tinySTL/*.cpp)

OBJS =$(patsubst test/%.cpp, objects/test/%.o, $(SRC_TEST)) \
	  $(patsubst tinySTL/%.cpp, objects/tinySTL/%.o, $(SRC_STL))

all:$(OBJS)
	g++ $(GPPPARAMS) -g -o main $(OBJS)

run:all
	./main

debug:all
	cgdb main

objects/test/%.o:test/%.cpp
	mkdir -p $(@D)
	g++ -g $(GPPPARAMS) -o $@ -c $<

objects/tinySTL/%.o:tinySTL/%.cpp
	mkdir -p $(@D)
	g++ -g $(GPPPARAMS) -o $@ -c $<

clean:
	rm -rf objects main