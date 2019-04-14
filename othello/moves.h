/*
 * Data structure to help store a set of moves throughtout the game. Is was some
 * sort of homemade jumbo-mombo in the original game, but the deque does its job
 * (and more) better, so now it's just an alias for the std::deque.
 */

#ifndef _MOVES_H
#define _MOVES_H

#include <utility>
#include <deque>

using GamePair = std::pair<unsigned, unsigned>;
using moves = std::deque<GamePair>;

#endif
