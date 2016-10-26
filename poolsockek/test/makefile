.PHONY:clean all


src = $(wildcard *.c)
obj = $(patsubst %.c,%,$(src))

all:$(obj)

$(obj):%:%.c
	gcc -lpthread -L./ -lmysocket $< -o $@

clean:
	rm $(obj)





