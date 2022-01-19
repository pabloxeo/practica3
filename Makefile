all: bin/Parchis

obj/main.o: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

bin/Parchis: obj/main.o
	g++ obj/main.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf ./obj/*.o ./bin/*