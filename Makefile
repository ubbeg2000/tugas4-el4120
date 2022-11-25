udp-client:
	gcc -o udp-client udp-server-client/client.c lib/date.c -lws2_32

udp-server:
	gcc -o udp-server udp-server-client/server.c -lws2_32

tcp-client:
	gcc -o tcp-client tcp-server-client/client.c lib/date.c -lws2_32

tcp-server:
	gcc -o tcp-server tcp-server-client/server.c -lws2_32

tcp:
	$(MAKE) tcp-client
	$(MAKE) tcp-server

udp:
	$(MAKE) udp-client
	$(MAKE) udp-server

all:
	$(MAKE) udp
	$(MAKE) tcp

clean:
	del *.exe