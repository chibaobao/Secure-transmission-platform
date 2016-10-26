ALL:accept send
accept:./src/accept.c
	gcc  -I ./inc -L./lib/ -litcastsocket -l appcryptapi ./src/accept.c ./src/cfg_op.c -o accept
send:./src/send.c
	gcc  -I ./inc -L./lib/ -litcastsocket -l appcryptapi ./src/send.c  ./src/cfg_op.c -o send
clean:
	rm accept send

.PNONY:clean
