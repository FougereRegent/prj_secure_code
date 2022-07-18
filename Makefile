NAME_SERVER=bin
NAME_TIME_SET=ts
NAME_CLIENT=$(NAME_SERVER)

.PHONY=clean

install: compil
	mkdir -p /bin/NC
	mv ./SERV/$(NAME_SERVER) /bin/NC/server_nc
	mv ./TS/$(NAME_TIME_SET) /bin/NC/ts
	mv ./client/$(NAME_CLIENT) /bin/NC/nc_client
	ln /bin/NC/server_nc /bin/server_nc
	ln /bin/NC/nc_client /bin/nc_client
	@mkdir -p /etc/NC/
	@cp ./TS/template.txt /etc/NC/.
compil:
	make -C ./SERV/.
	make -C ./TS/.
	make -C ./client/.

clean:
	rm -f  /bin/nc_client /bin/server_nc
	rm -rf /bin/NC
	rm -rf /etc/NC


