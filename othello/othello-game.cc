#include "othello-game.h"
#include <iostream>
#include <utility>
#include <array>

// Constructor.
game::game()
{
    // Setup the starting tiles. More information cab be found:
    // https://en.wikipedia.org/wiki/Reversi#Rules
    _gameBoard.setTile(3, 3, piece::WHITE);
    _gameBoard.setTile(3, 4, piece::BLACK);
    _gameBoard.setTile(4, 3, piece::BLACK);
    _gameBoard.setTile(4, 4, piece::WHITE);
    _gameInitialized = true;

    //Initialize the neighbour system
    initNewNeighbours();
}

// All eight combinations of pairs { [-1, 1], [-1, 1] } with { 0, 0 } excluded.
const static std::array<std::pair<int, int>, 8> seq_exclusive { {
    { -1, -1 }, { -1, 0 }, { -1, 1 },
    {  0, -1 }, /*     */  {  0, 1 },
    {  1, -1 }, {  1, 0 }, {  1, 1 } 
} };

// The make move method!
bool game::makeMove(unsigned x, unsigned y, piece color)
{
    /*
     * 1.  Test if it is the players turn.
     * 2.  Test if there are any neighbours.
     * 3.  Test if the tile is empty.
     * 4.  Test the tiles recursivly, and possible make the move.
     * 5.  Test if the move was legit.
     * 6.  Test if the opponent can make any moves, and change move accordingly.
     *(7.) Test if the game is over.
     */

    bool moveSucceded = false;

    // You cannot make a move if it is not your turn.
    if (testPlayerTurn() != color)
    {
        return false;
    }

    // Test if the desiered tile is empty.
    if (piece::EMPTY != _gameBoard.testTile(x, y))
    {
        return false;
    }

    // Test if the piece has any neighbours. You can for sure not make any moves
    // if you don't have any neighbours. 
    if (_neighbourBoard.testTile(x, y) != neighbourPiece::HN)
    {
        return false;
    }

    // Start testing and flipping surrouning tiles.
    for (auto &pair : seq_exclusive)
    {
        int dx = pair.first, dy = pair.second;
        if (testLegitRowTemplate(x, y, dx, dy, color, true))
        {
            flipRowTemplate(x, y, dx, dy, color);
            moveSucceded = true;
        }
    }
    if (moveSucceded)
    {
        // Set your own tile.
        _gameBoard.setTile(x, y, color);
    }

    // If the move succeded, add the tiles around it to the neighbour system. 
    // Also check if the opponent can make any move.*/
    if (moveSucceded)
    {
        // Add to neighboursystem (Seems fine)
        for (auto &pair : seq_exclusive)
        {
            int dx = pair.first, dy = pair.second;
            _neighbourBoard.setTile(x - dx, y - dy, neighbourPiece::HN);
        }

        // Test if the opponent can make any move.
        if ( getLegitMoves(reverseColor(color)).empty() )
        {
            // Test if the move-maker can't make any move
            if (getLegitMoves(color).empty()) 
            {
                _gameOver = true;
            }
            return moveSucceded;
        }
        else 
        {
            _playerTurn = reverseColor(color);
            return moveSucceded;
        }
    }

    // Return whether the made move succeded or not. (If it gets to this point,
    // the move has for sure failed.
    return moveSucceded;
}

// Test tile method
piece game::testTile(unsigned x, unsigned y) const
{
    if (x > 7 || y > 7) 
    {
        // Out of bounds.
        return piece::OOB;
    }
    else 
    {
        // Return tile.
        return _gameBoard.testTile(x, y);
    }
}



// Test if a move i legit to do in the games current state.
bool game::testLegitMove(unsigned x, unsigned y, piece color) const
{
    if (piece::EMPTY != _gameBoard.testTile(x, y)) 
    {
        // The is already taken.
        return false;
    }

    for (auto &pair : seq_exclusive)
    {
        int dx = pair.first, dy = pair.second;
        if (testLegitRowTemplate(x, y, dx, dy, color, true))
            return true;
    }

    // This move would not flip any other tile, and is therefor NOT legit.
    return false;
}

// Get all the legit moves.
moves game::getLegitMoves(piece color) const
{
    moves tempMoveStruct;
    for (unsigned x = 0; x < 8; x++) {
        for (unsigned y = 0; y < 8; y++)
        {
            if (_neighbourBoard.testTile(x,y) == neighbourPiece::HN)
            {
                if (testLegitMove(x, y, color)) 
                {
                    tempMoveStruct.push_back(GamePair(x, y));
                }
            }
        }
    }
    return tempMoveStruct;
}

// Help methods for 'testNeighbours' method.
bool game::testNeighbourTemplate(
    unsigned x,
    unsigned y,
    unsigned deltax,
    unsigned deltay) const
{
    //Test if the tile is EMPTY.
    piece testPiece = _gameBoard.testTile(x + deltax, y + deltay);
    return testPiece == piece::BLACK || testPiece == piece::WHITE;
}

// Help method for the 'testLegitMove' method.
bool game::testLegitRowTemplate(
    unsigned x,
    unsigned y,
    unsigned deltax,
    unsigned deltay,
    piece testingColor,
    bool first) const
{
    if (first)
    {
        // First call to test. This cannot return true.
        piece tempTestTile = _gameBoard.testTile(x + deltax, y + deltay);
        if (tempTestTile == reverseColor(testingColor))
        {
            return testLegitRowTemplate(
                    x + deltax,   // x
                    y + deltay,   // y
                    deltax,       // deltax
                    deltay,       // deltay
                    testingColor, // testingcolor
                    false);       // first
        }
        else
        {
            return false;
        }
    }
    else
    {
        // Second call to test. It's okey to return true.
        piece tempTestTile = _gameBoard.testTile(x + deltax, y + deltay);
        if (tempTestTile == testingColor)
        {
            return true;
        }
        if (tempTestTile == reverseColor(testingColor))
        {
            return testLegitRowTemplate(
                    x + deltax,   // x
                    y + deltay,   // y
                    deltax,       // deltax
                    deltay,       // deltay
                    testingColor, // testingcolor
                    false);       // first
        }
        if (tempTestTile == piece::OOB || tempTestTile == piece::EMPTY)
        {
            return false;
        }
        return false;
    }
}

// Returns the opposite color of the input.
piece game::reverseColor(piece color) const
{
    if (color == piece::BLACK) 
    {
        return piece::WHITE;
    }
    else if (color == piece::WHITE) 
    {
        return piece::BLACK;
    }
    else 
    {
        return piece::BADPICE;
    }
}

// Method for flipping tiles in a row.
void game::flipRowTemplate(
        unsigned x, unsigned y, 
        unsigned deltax, unsigned deltay, 
        piece flipToColor)
{
    if (testTile(x + deltax, y + deltay) == reverseColor(flipToColor))
    {
        _gameBoard.setTile(x + deltax, y + deltay, flipToColor);
        flipRowTemplate(x + deltax, y + deltay, deltax, deltay, flipToColor);
    }
}

// Method for initializing the neighbour-system.
void game::initNewNeighbours()
{
    //Set all pieces to not have neighbours.
    for (unsigned x = 0; x < 8; x++) 
    {
        for (unsigned y = 0; y < 8; y++)
        {
            _neighbourBoard.setTile(x, y, neighbourPiece::DNHN);
        }
    }

    //Set the eight middle pieces to have neighbours.
    for (unsigned x = 2; x < 6; x++)
    {
        for (unsigned y = 2; y < 6; y++)
        {
            _neighbourBoard.setTile(x, y, neighbourPiece::HN);
        }
    }
}

// Returns the color of the player that has its turn.
piece game::testPlayerTurn() const
{
    return _playerTurn;
}

// Returns a copy of the current board state.
board game::getBoard() const
{
    board tempBoard = _gameBoard;
    return tempBoard;
}

// Returns true if the game is over, false otherwise.
bool game::testGameOver() const
{
    return _gameOver;
}

// Method for testing the white players score.
unsigned game::testScoreWhite() const
{
    unsigned score = 0;
    for (unsigned y = 0; y < 8; y++) 
    {
        for (unsigned x = 0; x < 8; x++)
        {
            if (_gameBoard.testTile(x, y) == piece::WHITE)
            {
                score++;
            }
        }
    }
    return score;
}

// Method for testing the black players turn.
unsigned game::testScoreBlack() const
{
    unsigned score = 0;
    for (unsigned y = 0; y < 8; y++) 
    {
        for (unsigned x = 0; x < 8; x++)
        {
            if (_gameBoard.testTile(x, y) == piece::BLACK)
            {
                score++;
            }
        }
    }
    return score;
}
