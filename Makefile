CC = g++ -std=c++11 -Wall -Wextra -Wpedantic -Weffc++ -O3
LINK = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all othello frontend binary clean

all: othello frontend binary

othello:
	$(MAKE) -C othello

frontend:
	$(MAKE) -C frontend

binary:
	$(CC) $(wildcard build/*.o) $(LINK) -o game

clean:
	-@rm -rfv build
	-@rm -rfv game
