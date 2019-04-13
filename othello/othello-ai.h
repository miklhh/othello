/* 
 * Class AI.
 * This is the othello ai. For the record it only has one important method, 
 * alphabeta. This is going to be wider later on. 
 *
 * Good settings for the AI: (Updated 2016-06-16)
 * Good settings for the AI: (Updated 2019-04-13)
 * 1. Let the search depth be around 7 in alphabeta.
 * 2. Long time since I saw this last haha.
 *
 * Methods:
 * Public:
 * -- move evaluateMove ()             Make AI evaluate a new move.
 * -- void setAiColor(color)           Switch AI color.
 * -- piece getAiColor()               Get AI color.
 * -- void setCurrentGame(game)        Give AI the current game.
 * 
 * Private:
 * -- piece reverseColor(color)        Reverses the given color.
 * -- makeMini(see def.)               Makes a "mini" out of arguments.
 * -- int getSearchDepth(int)          Returns the search depth.
 * -- int heuristicValue(game, piece)  Returns the heuristic value of a board.
 * --
*/

#ifndef _OTHELLO_AI_H
#define _OTHELLO_AI_H

#include <utility>
#include "othello-game.h"

typedef std::pair<int, std::pair<unsigned int, unsigned int>> mini;
typedef std::pair<unsigned int, unsigned int> move;

class ai
{
public:

    // Public methods. Methods for interacting with the AI and its different
    // components.
    move  evaluateMove();
    void  setAiColor(piece color);
    void  setCurrentGame(game newGame);
    piece getAiColor() const;
    void  setSearchDepth(unsigned int searchDepth);
    
private:
    // The alphabeta algorithm with alpha-beta prunings.
    mini alphaBeta(game node,
                   int depth,
                   bool maximizingPlayer,
                   piece maximizingColor,
                   int alpha,
                   int beta,
                   move moveMade,
                   bool lateGame);

    // Heurisitc value function and its help functions.
    int heuristicValue(game _game, piece maximizingColor);
    int mobilityTester(game _game, piece maximizingColor);
    int cornerTester(game _game, piece maximizingColor);
    int fieldTester(game _game, piece maximizingColor);
    int tileWeight(unsigned int x, unsigned int y, game _game, piece maximizingColor);

    // Other private methods.
    piece reverseColor(piece color) const;
    mini  makeMini(int value, unsigned int x, unsigned int y) const;
    int   getSearchDepth();

private:
    // Ai local field variables.
    game     _currentGame{};
    piece    _aiColor{ piece::WHITE };
    unsigned _moveCount{ 0 };
    unsigned _searchDepth{ 7 };
};

#endif
