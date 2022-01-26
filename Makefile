all: bin/Parchis

obj/main.o: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o -I include/

obj/ParchisGUI.o: src/ParchisGUI.cpp
	g++ -c src/ParchisGUI.cpp -o obj/ParchisGUI.o -I include/

bin/Parchis: obj/main.o obj/ParchisGUI.o
	g++ obj/main.o obj/ParchisGUI.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf ./obj/*.o ./bin/*