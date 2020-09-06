ASM = nasm
# S_SOURCE=$(wildcard src/*.s)
# S_OBJECT=$(patsubst,objects/%.c,$(S_SOURCE))

objects/boot/%.bin:src/boot/%.s
	mkdir -p $(@D)
	$(ASM) -I include -o $@ $<

clean:
	rm -rf objects