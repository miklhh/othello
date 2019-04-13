/*
 * Frontend for othello game.
 */

#include "../othello/othello-board.h"
#include <SFML/Graphics.hpp>
#include <utility>
#include "../othello/moves.h"

class frontend
{
public:
    frontend();
    ~frontend() = default;

    // Methods:
    void drawBoard(const board &b);
    void drawUI(piece playerTurn);
    void drawLegitMoves(moves legitMoves, piece color);

public:
    // Renderwindow.
    sf::RenderWindow window;

    // Textures.
    sf::Texture blackTexture{};
    sf::Texture whiteTexture{};
    sf::Texture boardTexture{};
    sf::Texture blackPlayerTurnTexture{};
    sf::Texture whitePlayerTurnTexture{};
    sf::Texture gameInfoTexture{};

    // Sprites.
    sf::Sprite blackSprite{};
    sf::Sprite whiteSprite{};
    sf::Sprite boardSprite{};
    sf::Sprite blackPlayerTurnSprite{};
    sf::Sprite whitePlayerTurnSprite{};
    sf::Sprite gameInfoSprite{};
};
