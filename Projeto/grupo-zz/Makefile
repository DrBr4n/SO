# -*- MakeFile -*-

all: server client

server: bin/aurrasd

client: bin/aurras

bin/aurrasd: obj/aurrasd.o obj/parse_entry.o
	gcc -g obj/aurrasd.o obj/parse_entry.o -o bin/aurrasd

obj/aurrasd.o: src/aurrasd.c
	gcc -Wall -g -c src/aurrasd.c -o obj/aurrasd.o

obj/parse_entry.o: src/parse_entry.c
	gcc -Wall -g -c src/parse_entry.c -o obj/parse_entry.o

bin/aurras: obj/aurras.o
	gcc -g obj/aurras.o -o bin/aurras

obj/aurras.o: src/aurras.c
	gcc -Wall -g -c src/aurras.c -o obj/aurras.o

clean:
	rm obj/* tmp/* bin/{aurras,aurrasd}

test:
	bin/aurras
	bin/aurras status
	bin/aurras transform samples/sample-1.m4a output.m4a alto eco rapido