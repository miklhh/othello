#include "othello-board.h"

// Constructor for board. The four middlepieces has to be set manually.
board::board()
{
    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++)
        {
            //Set the boardtiles to empty.
            _gameBoard[x][y] = piece::EMPTY;
        }
    }
}

// Method setTile.
piece board::setTile(unsigned int x, unsigned int y, piece piece)
{
    // Make sure that you are on the board.
    if (x > 7 || y > 7)
    {
        return piece::OOB;
    } 
    else 
    {
        _gameBoard[x][y] = piece;
        return piece;
    }
}

// Method for testing a tile..
piece board::testTile(unsigned int x, unsigned int y) const noexcept
{
    if (x > 7 || y > 7) 
    {
        return piece::OOB;
    } 
    else 
    {
        return _gameBoard[x][y];
    }
}

// Methods for seting a tile.
neighbourPiece neighbourBoard::setTile(
        unsigned int x, unsigned int y, neighbourPiece piece)
{
    if (x > 7 || y > 7) 
    {
        return neighbourPiece::OOB;
    }
    else 
    {
        _neighbours[x][y] = piece;
        return piece;
    }
}

neighbourPiece neighbourBoard::testTile(unsigned int x, unsigned int y) 
    const noexcept
{
    if (x > 7 || y > 7) 
    {
        return neighbourPiece::OOB;
    }
    else 
    {
        return _neighbours[x][y];
    }
}
