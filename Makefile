all: bin/Parchis

obj/main.o: src/main.cpp
	g++ -g -c src/main.cpp -o obj/main.o -I include/ -std=c++14

obj/ParchisGUI.o: src/ParchisGUI.cpp
	g++ -g -c src/ParchisGUI.cpp -o obj/ParchisGUI.o -I include/ -std=c++14

obj/Parchis.o: src/Parchis.cpp
	g++ -g -c src/Parchis.cpp -o obj/Parchis.o -I include/ -std=c++14

obj/Board.o: src/Board.cpp
	g++ -g -c src/Board.cpp -o obj/Board.o -I include/ -std=c++14

obj/Dice.o: src/Dice.cpp
	g++ -g -c src/Dice.cpp -o obj/Dice.o -I include/ -std=c++14

obj/ClickableSprite.o: src/ClickableSprite.cpp
	g++ -g -c src/ClickableSprite.cpp -o obj/ClickableSprite.o -I include/ -std=c++14

obj/BoardSprite.o: src/BoardSprite.cpp
	g++ -g -c src/BoardSprite.cpp -o obj/BoardSprite.o -I include/ -std=c++14

obj/DiceSprite.o: src/DiceSprite.cpp
	g++ -g -c src/DiceSprite.cpp -o obj/DiceSprite.o -I include/ -std=c++14

obj/PieceSprite.o: src/PieceSprite.cpp
	g++ -g -c src/PieceSprite.cpp -o obj/PieceSprite.o -I include/ -std=c++14

obj/Player.o: src/Player.cpp
	g++ -g -c src/Player.cpp -o obj/Player.o -I include/ -std=c++14

obj/AIPlayer.o: src/AIPlayer.cpp
	g++ -g -c src/AIPlayer.cpp -o obj/AIPlayer.o -I include/ -std=c++14

obj/GUIPlayer.o: src/GUIPlayer.cpp
	g++ -g -c src/GUIPlayer.cpp -o obj/GUIPlayer.o -I include/ -std=c++14

obj/SpriteAnimator.o: src/SpriteAnimator.cpp
	g++ -g -c src/SpriteAnimator.cpp -o obj/SpriteAnimator.o -I include/ -std=c++14

obj/Button.o: src/Button.cpp
	g++ -g -c src/Button.cpp -o obj/Button.o -I include/ -std=c++14

obj/RectangularButton.o: src/RectangularButton.cpp
	g++ -g -c src/RectangularButton.cpp -o obj/RectangularButton.o -I include/ -std=c++14

bin/Parchis: obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/SpriteAnimator.o obj/DiceSprite.o obj/PieceSprite.o obj/BoardSprite.o obj/ClickableSprite.o obj/GUIPlayer.o obj/AIPlayer.o obj/Player.o
	g++ -g obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o obj/PieceSprite.o obj/BoardSprite.o obj/ClickableSprite.o obj/GUIPlayer.o obj/AIPlayer.o obj/Player.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf ./obj/*.o ./bin/*