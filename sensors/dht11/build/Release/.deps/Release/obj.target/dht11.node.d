cmd_Release/obj.target/dht11.node := g++ -shared -pthread -rdynamic  -Wl,-soname=dht11.node -o Release/obj.target/dht11.node -Wl,--start-group Release/obj.target/dht11/dht11.o -Wl,--end-group -lwiringPi