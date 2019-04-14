/*
 * This class represents a game of othello. It contains all the data and 
 * functionallity requiered to play a game of othello. It has some extra methods
 * to ease the work for the AI.
 *
 * Public Methods:
 * -- bool makeMove(x,y,color)      Use this method to make a move.
 * -- bool testLegitMove(x,y,color) Returns true if the move is legit.
 * -- moves getLegitMoves(color)    Returns all the legit moves.
 * -- piece testTile(x,y)           Returns the piece that stands on x,y.
 * -- board getBoard()              Return a copy of the game board.
 * -- bool testGameOver()           Returns true if the game is over.
 * -- unsigned testScoreWhite()     Returns white players score.
 * -- unsigned testScroeBlack()     Returns black players score.
 * -- piece reverseColor(color)     Returns the opposite color.
 *
 */

#ifndef _OTHELLO_GAME_H
#define _OTHELLO_GAME_H

#include "othello-board.h"
#include "moves.h"
#include <deque>

class game
{
private:
    /*
     * The physicl representation of the data. For more information about the 
     * class board, please look in the othello-board header file.
     */
    board _gameBoard{};

    /*
     * The neighbour-board. This object keeps tracks of the tiles that should be
     * tested by the functions make-move and get legit moves! This is mostly 
     * implemented to speed up the process of getting all the legit move, so 
     * that the ai can work fast.
     */
    neighbourBoard _neighbourBoard{};

    bool  _gameInitialized{ false };    // Is the game initialized?
    bool  _gameOver{ false };           // Is the game over?
    piece _playerTurn{ piece::BLACK };  // Whos turn is it?

public:
    game();

    /*
     * Methods important for playing the game. Rules can be found:
     * https://en.wikipedia.org/wiki/Reversi#Rules
     */
    bool  makeMove(unsigned x, unsigned y, piece color);
    piece testPlayerTurn() const;
    piece testTile(unsigned x, unsigned y) const;
    moves getLegitMoves(piece color) const;
    bool  testLegitMove(unsigned x, unsigned y, piece color) const;

    /*
     * Methods impotant for displaying game information.
     */
    unsigned testScoreWhite() const;
    unsigned testScoreBlack() const;
    piece    reverseColor(piece color) const;
    board    getBoard() const;
    bool     testGameOver() const;


private:
    void initNewNeighbours();

    bool testNeighbourTemplate(
            unsigned x, unsigned y, 
            unsigned deltax, unsigned deltay) const;

    bool testLegitRowTemplate(
            unsigned x, unsigned y,
            unsigned deltax, unsigned deltay,
            piece testingColor, bool first) const;

    void flipRowTemplate(
            unsigned x, unsigned y,
            unsigned deltax, unsigned deltay,
            piece flipToColor);
};

#endif
