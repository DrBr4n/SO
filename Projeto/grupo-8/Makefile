all: server client transform

server: bin/aurrasd

client: bin/aurras

transform: bin/transform

bin/aurrasd: obj/aurrasd.o
	gcc -g obj/aurrasd.o -o bin/aurrasd

obj/aurrasd.o: src/aurrasd.c
	gcc -Wall -g -c src/aurrasd.c -o obj/aurrasd.o

bin/aurras: obj/aurras.o
	gcc -g obj/aurras.o -o bin/aurras

obj/aurras.o: src/aurras.c
	gcc -Wall -g -c src/aurras.c -o obj/aurras.o

bin/transform: obj/transform.o
	gcc -g obj/transform.o -o bin/transform

obj/transform.o: src/transform.c
	gcc -Wall -g -c src/transform.c -o obj/transform.o

clean:
	rm obj/* tmp/* bin/aurras bin/aurrasd

test:
	bin/aurras transform ../samples/sample-1-so.m4a ../output/sample-1-so-alto.mp3 alto
	bin/aurras transform ../samples/sample-1-so.m4a ../output/sample-1-so-baixo.mp3 baixo
	bin/aurras transform ../samples/sample-1-so.m4a ../output/sample-1-so-ecoAltoEcoLento.mp3 eco alto eco lento
	bin/aurras transform ../samples/sample-1-so.m4a ../output/sample-1-so-rapidoRapidoAltoEco.mp3 rapido rapido alto eco
	bin/aurras transform ../samples/sample-1-so.m4a ../output/sample-1-so-altoBaixoEcoRapidoLento.mp3 alto baixo eco rapido lento
