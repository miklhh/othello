/*
 * Main file for the othello game.
 */

#include "frontend.h"
#include "../othello/othello-game.h"
#include "../othello/othello-ai.h"
#include <SFML/Graphics.hpp>
#include <iostream>

static game othello;
static ai   othelloAi;

// Convert a mouse click to a tile click.
std::pair<int, int> mouseToTile(float mouse_x, float mouse_y)
{
    return { mouse_x / 80, mouse_y / 80 };
}

int main()
{
    // Setup colors.
    constexpr piece humanColor = piece::BLACK;
    constexpr piece aiColor = piece::WHITE;
    othelloAi.setAiColor(aiColor);

    frontend frontend;
    while ( frontend.window.isOpen() )
    {
        // Clear the screen.
        frontend.window.clear();

        // Draw the board
        frontend.drawBoard(othello.getBoard());
        frontend.drawUI(othello.testPlayerTurn());
        if (othello.testPlayerTurn() == humanColor)
        {
            frontend.drawLegitMoves(
                    othello.getLegitMoves(humanColor), humanColor);
        }

        // Display.
        frontend.window.display();

        // Test if the game is over.
        if (othello.testGameOver())
        {
            frontend.window.close();
            break;
        }

        // Make a move if it is the AI turn.
        if (othello.testPlayerTurn() == aiColor)
        {
            othelloAi.setCurrentGame(othello);
            move aiMove = othelloAi.evaluateMove();
            int x = aiMove.first, y = aiMove.second;
            if ( !othello.makeMove(x, y, aiColor) )
            {
                std::cerr << "AI FAILED MAKING MOVE. FATAL!" << std::endl;
                exit(-1);
            }
        }

        sf::Event event;
        while ( frontend.window.pollEvent(event) )
        {
            float mouse_x;
            float mouse_y;
            std::pair<int, int> tile;
            switch (event.type)
            {
                case sf::Event::Closed:
                    frontend.window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    mouse_x = sf::Mouse::getPosition(frontend.window).x;
                    mouse_y = sf::Mouse::getPosition(frontend.window).y;
                    tile = mouseToTile(mouse_x, mouse_y);
                    othello.makeMove(tile.first, tile.second, humanColor);

                default:
                    break;
            }
        }

        // Sleep.
        sf::sleep( sf::milliseconds(16) );
    }

    if ( othello.testGameOver() )
    {
        std::cout << "Game over: " << std::endl;
        std::cout << "    AI:    " << othello.testScoreWhite() << std::endl;
        std::cout << "    HUMAN: " << othello.testScoreBlack() << std::endl;
    }

    return 0;
}
