/*
 * This is a structure for storing many moves in.
 * Use getMove, to get a move out of the structure. When using getMove, the
 * structure automaticlly removes that move from the structure. When there is no
 * move left stored in the structure, getMove will return a pair '(100 . 100).
 * It also contains a typedef for string a move inside it, GamePair.
 */

#ifndef _MOVES_H
#define _MOVES_H

#include <vector>
#include <utility>

typedef std::pair<unsigned int, unsigned int> GamePair;

class moves 
{
public:
    bool testEmpty();
    void addMove(unsigned x, unsigned y);
    int getLength();
    GamePair getMove();

private:
    std::vector<std::pair<unsigned int,unsigned int>> _datastruct{};
};

#endif
