src = $(wildcard ./src/*.c)
inc = $(wildcard ./src/*.h)
obj = $(patsubst ./src/%.c,%,$(src))

ALL: $(obj)
$(obj):$(src)
	gcc $(src)  -I ./inc/ -L ./lib/ -lmymessagereal -o $(obj)

clean:
	rm $(obj)
.PHONY: clean ALL
