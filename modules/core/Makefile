all: encoding.o random_data.o shell.o socket.o ruby_payloads.o

encoding.o: encoding.c
	gcc -fPIC -Wall -g -c encoding.c

random_data.o: random_data.c
	gcc -fPIC -Wall -g -c random_data.c

shell.o: shell.c
	gcc -fPIC -Wall -g -c shell.c

socket.o: socket.c
	gcc -fPIC -Wall -g -c socket.c

ruby_payloads.o: payloads/ruby_payloads.c
	gcc -fPIC -Wall -g -c payloads/ruby_payloads.c

clean:
	rm -rf *o
