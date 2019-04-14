#include "frontend.h"
#include "../othello/moves.h"
#include "../othello/othello-board.h"
#include <stdexcept>
#include <utility>

// Default constructor.
frontend::frontend() : window(sf::VideoMode(640, 768), "Othello", sf::Style::Close)
{
    // Load all textures.
    if ( !blackTexture.loadFromFile("images/black.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }
    if ( !whiteTexture.loadFromFile("images/white.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }
    if ( !boardTexture.loadFromFile("images/board.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }
    if ( !blackPlayerTurnTexture.loadFromFile("images/playerTurnBlack.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }
    if ( !whitePlayerTurnTexture.loadFromFile("images/playerTurnWhite.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }
    if ( !gameInfoTexture.loadFromFile("images/infoPanel.png") )
    {
        throw std::runtime_error("Could not load image from file.");
    }

    // Set the sprite textures.
    blackSprite.setTexture(blackTexture);
    whiteSprite.setTexture(whiteTexture);
    boardSprite.setTexture(boardTexture);
    blackPlayerTurnSprite.setTexture(blackPlayerTurnTexture);
    whitePlayerTurnSprite.setTexture(whitePlayerTurnTexture);
    gameInfoSprite.setTexture(gameInfoTexture);
    
    // Set UI positions.
    blackPlayerTurnSprite.setPosition(10, 650);
    whitePlayerTurnSprite.setPosition(10, 650);
    gameInfoSprite.setPosition(0, 640);
}


// Rendering method.
void frontend::drawBoard(const board &b)
{
    // Draw the background board.
    window.draw(boardSprite);

    // Draw the tiles on the board.
    const int X_SIZE = 8, Y_SIZE = 8;
    for (int x = 0; x < X_SIZE; ++x)
    {
        for (int y = 0; y < Y_SIZE; ++y)
        {
            if ( b.testTile(x, y) == piece::BLACK )
            {
                blackSprite.setPosition( float(x) * 80.0f, float(y) * 80.0f );
                window.draw(blackSprite);
            }
            else if ( b.testTile(x, y) == piece::WHITE )
            {
                whiteSprite.setPosition( float(x) * 80.0f, float(y) * 80.0f );
                window.draw(whiteSprite);
            }
        }
    }
}


// Draw the UI.
void frontend::drawUI(piece playerTurn)
{
    // Draw the info panel.
    window.draw(gameInfoSprite);

    // Draw the player turn.
    if (playerTurn == piece::WHITE)
    {
        window.draw(whitePlayerTurnSprite);
    }
    else if (playerTurn == piece::BLACK)
    {
        window.draw(blackPlayerTurnSprite);
    }
    else
    {
        std::string error = std::string(__FILE__) + std::string("(") + std::to_string(__LINE__) + std::string(")");
        throw std::runtime_error(std::string("Error in file: ") + error);
    }
}

// Draw the possible moves for a player.
void frontend::drawLegitMoves(moves legitMoves, piece color)
{
    while ( legitMoves.size() > 0 )
    {
        GamePair move = legitMoves.front(); legitMoves.pop_front();
        int x = move.first, y = move.second;
        if (color == piece::BLACK)
        {
            blackSprite.setPosition( float(x) * 80.0f, float(y) * 80.0f );
            blackSprite.setColor( sf::Color(255, 255, 255, 20) );
            window.draw(blackSprite);
        }
        else
        {
            whiteSprite.setPosition( float(x) * 80.0f, float(y) * 80.0f );
            whiteSprite.setColor( sf::Color(255, 255, 255, 20) );
            window.draw(whiteSprite);
        }

    }

    // Restore transparancy
    blackSprite.setColor( sf::Color(255, 255, 255, 255) );
    whiteSprite.setColor( sf::Color(255, 255, 255, 255) );
}
