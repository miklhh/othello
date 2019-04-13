CC = g++
LINK = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: othello frontend binary all clean

othello:
	$(MAKE) -C othello

frontend:
	$(MAKE) -C frontend

binary:
	$(CC) $(wildcard build/*.o) $(LINK) -o game

all: othello frontend binary

clean:
	-@rm -rfv build
	-@rm -rfv game
