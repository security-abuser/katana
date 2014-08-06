
all: katana

katana: katana.o module.o katana_shell.o katana_exploit.o
	cd ./modules/core/; make
	cd ./modules/exploits; make
	gcc -g -ldl katana.o module.o katana_shell.o katana_exploit.o -lreadline -o katana

katana.o: katana.c
	gcc -c katana.c -o katana.o

module.o: module.c
	gcc -c module.c -o module.o

katana_shell.o: katana_shell.c
	gcc -c katana_shell.c -o katana_shell.o


katana_exploit.o: katana_exploit.c
	gcc -c katana_exploit.c -o katana_exploit.o

clean:
	cd ./modules/core/; rm -rf *.o
	cd ./modules/exploits; rm -rf *.o
	rm -rf katana *.o
