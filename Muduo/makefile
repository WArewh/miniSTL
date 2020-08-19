PATH_BASE=base
PATH_NET=net

CC=clang++

SRC_BASE=$(wildcard base/src/*.cc)
SRC_NET=$(wildcard net/src/*.cc)

OBJS=$(patsubst base/src/%.cc,objects/base/%.o,$(SRC_BASE)) \
	 $(patsubst net/src/%.cc,objects/net/%.o,$(SRC_NET))

all:$(OBJS)

objects/base/%.o:base/src/%.cc
	mkdir -p $(@D)
	$(CC) -g -I$(PATH_BASE) -o $@ -c $<

objects/net/%.o:net/src/%.cc
	mkdir -p $(@D)
	$(CC) -g -I$(PATH_NET) -o $@ -c $<

clean:
	rm -rf objects