.PHONY:all
all:tcpserver tcpclient

tcpserver:Main.cc
	g++ -o $@ $^ -std=c++11
tcpclient:TcpClient.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f tcpserver tcpclient
	