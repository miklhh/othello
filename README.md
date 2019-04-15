# Othello
This application is a remake of my old project from the course [TDDC74 - Programming abstraction and modeling](https://www.ida.liu.se/~TDDC74/). It's an implementation of the board game [Othello](https://sv.wikipedia.org/wiki/Othello) with a simple game theory based AI to play against. The original implementation was made in [DrRacket](https://racket-lang.org/) and the AI was easily beaten by users with only a sliver of experience in the game. During that summer break (2016) I revisited that project and decided to create a remake with C++, this time with the goal to make the AI ~~more difficult~~ *more bothersome* to beat. This repository contains that remake with some minor code touches and an [SFML](https://www.sfml-dev.org/) based frontend. Can you beat the new and *improved* AI?

## Short AI descripton
* Based on the [minimax](https://en.wikipedia.org/wiki/Minimax) decistion rule with [alpha-beta](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) prunings.
* Uses heuristic valuing to...
  * Minimize the opponents available moves and maximize AI available moves.
  * Force opponent to give away corrners.
  * Maximize the tile difference between AI and its opponent.

## Dependencies
The game and AI are implemented using pure C++11 but the frontend is based on [SFML](https://www.sfml-dev.org/). To build the entire game, including frontend, simply invoke `make all` from the repository root.
