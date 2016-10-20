src = $(wildcard ./src/*.c)
libo = $(patsubst ./src/%.c,%.o,$(src))
obj = libmymessagereal.so

$(obj): $(libo)
	gcc -shared  $(libo) -o $(obj)
	cp $(obj) $(HOME)/lib2/
$(libo):$(src)
	gcc -fPIC -I ./inc/ $(src) -c
clean_o:
		rm *.o
clean:
	rm *.o
	rm $(obj)
.PHONY: clean clean_o

