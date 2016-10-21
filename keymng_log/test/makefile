.PHONY:clean all


src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c,%,$(src))

all:$(obj)

$(obj):%:./src/%.c
	gcc -I inc keymnglog.c $< -o $@

clean:
	rm $(obj)





