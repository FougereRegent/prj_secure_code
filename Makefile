NAME_SERVER=bin
NAME_TIME_SET=ts

.PHONY=clean

install: compil
	ln ./SERV/$(NAME_SERVER) ./server
	ln ./TS/$(NAME_TIME_SET) ./ts
	@mkdir -p /etc/NetworkClock/
	@cp ./TS/template.txt /etc/NetworkClock/.
compil:
	make -C ./SERV/.
	make -C ./TS/.

clean:
	rm -f server
	rm -f $(NAME_TIME_SET)
	rm -f ./SERV/$(NAME_SERVER)
	rm -f ./TS/$(NAME_TIME_SET)


