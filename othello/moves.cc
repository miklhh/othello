#include "moves.h"
#include <utility>
#include <vector>

// Test if the move-structure is empty.
bool moves::testEmpty()
{
    return _datastruct.empty();
}

// Add a move to the move-structure.
void moves::addMove(unsigned int x, unsigned int y)
{
    GamePair tempPair;
    tempPair = std::make_pair(x,y);
    _datastruct.push_back(tempPair);
}

// Get a move from the move-structure (also removes that move from the structure).
GamePair moves::getMove()
{
    if (!testEmpty())
    {
        GamePair tempPair = _datastruct.back();
        _datastruct.pop_back();
        return tempPair;
    }
    else 
    {
        GamePair badEnd;
        badEnd = std::make_pair<unsigned int, unsigned int>(100, 100);
        return badEnd;
    }
}

// Get the lenght of the move-structure.
int moves::getLength()
{
    return _datastruct.size();
}
