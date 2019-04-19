/* 
 * This header file holds all the 'low-level' physical data that the othello/
 * reversi game uses. The class board and neighbourBoard is used for storing the 
 * moves and neighbours in.
 */

#ifndef _OTHELLO_BOARD_H
#define _OTHELLO_BOARD_H

enum class piece
{
    EMPTY,  // EMPTY
    WHITE,  // WHITE
    BLACK,  // BLACK
    OOB,    // Out-of-bound.
    BADPICE // Return if somethign goes wrong.
};
enum class neighbourPiece
{
    HN,     // Has neighbour.
    DNHN,   // Doesn't have neighbour.
    OOB,    // Out of bounds.
};

/* 
 * Class for the neighbour-board system. The neighbour system is used to ease 
 * the workload for the ai. The neighbour-system gives information about which 
 * tiles that has to be tested and not.
 */
class neighbourBoard
{
public:
    // Public methods
    neighbourPiece setTile(unsigned x, unsigned y, neighbourPiece piece);
    neighbourPiece testTile(unsigned x, unsigned y) const noexcept;

private:
    // The physical data
    neighbourPiece _neighbours[8][8];
};


/* 
 * Class for the board. The class 'board' is where the data for the othello 
 * board is stored. 
 */
class board
{
    
public:
    board();

    // Public methods.
    piece setTile(unsigned x, unsigned y, piece p);
    piece testTile(unsigned x, unsigned y) const noexcept;

private:
    //The physical data of the board.
    piece _gameBoard[8][8];
};

#endif
