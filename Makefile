all: bin/Parchis

obj/main.o: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o -I include/ -std=c++14

obj/ParchisGUI.o: src/ParchisGUI.cpp
	g++ -c src/ParchisGUI.cpp -o obj/ParchisGUI.o -I include/ -std=c++14

obj/Parchis.o: src/Parchis.cpp
	g++ -c src/Parchis.cpp -o obj/Parchis.o -I include/ -std=c++14

obj/Board.o: src/Board.cpp
	g++ -c src/Board.cpp -o obj/Board.o -I include/ -std=c++14

obj/Dice.o: src/Dice.cpp
	g++ -c src/Dice.cpp -o obj/Dice.o -I include/ -std=c++14

obj/DiceSprite.o: src/DiceSprite.cpp
	g++ -c src/DiceSprite.cpp -o obj/DiceSprite.o -I include/ -std=c++14

obj/SpriteAnimator.o: src/SpriteAnimator.cpp
	g++ -c src/SpriteAnimator.cpp -o obj/SpriteAnimator.o -I include/ -std=c++14

bin/Parchis: obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o
	g++ obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf ./obj/*.o ./bin/*