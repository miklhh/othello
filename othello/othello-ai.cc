#include "othello-ai.h"
#include "moves.h"

// This is the function that is used in order to evaluate a move.
// Do not use this method if the AI is not supposed to make a move.
move ai::evaluateMove()
{
    // The search depth of the alpha-beta algorithm.
    int searchDepth = getSearchDepth();

    mini tempMini;
    if (_moveCount < 24)
    {
        // In the early stages of the game we use the heuristic function to try
        // to get a good position in the game.
        tempMini = alphaBeta(
            _currentGame,         // Game.
            searchDepth,          // Search depth.
            true,                 // Maximize player.
            _aiColor,             // The color.
            -5000,                // Alpha.
            5000,                 // Beta.
            std::make_pair(0, 0), // Needed arg to start minimax.
            true);                // Use the heuristic evaluationfunction?
    }
    else 
    { 
        // In the late stages of the game we can search all the way to the end,
        // or atleast alot deeper.
        tempMini = alphaBeta(
            _currentGame,         // Game.
            12,                   // Search depth.
            true,                 // Maximize player.
            _aiColor,             // The color.
            -5000,                // Alpha.
            5000,                 // Beta.
            std::make_pair(0, 0), // Needed arg to start minimax.
            false);               // Use the heuristic evaluationfunction?
    }
    _moveCount++;
    return tempMini.second;
}

// Alpha-beta (minimax) algorithm! This alpha-beta algorithm is in alpha stage.. 
// soon the beta-release will come... haha.
mini ai::alphaBeta(
        game node, 
        int depth, 
        bool maximizingPlayer, 
        piece maximizingColor, 
        int alpha, 
        int beta, 
        move moveMade, 
        bool useHeuFunc)
{
    // Test for terminal node
    if (node.testGameOver() || depth == 0)
    {
        // What stage of the game the othello game is in? Should the heuristic 
        // help function determine the value of the board?
        if (useHeuFunc)
        {
            // Store the return value, and return it.
            int tempValue = heuristicValue(node, maximizingColor);
            mini returnValue = std::make_pair(tempValue, moveMade);
            return returnValue;
        }
        else
        {
            // Store tempValue depending on who is being maximized for.
            int nodeValue{};
            if (maximizingColor == piece::WHITE)
            {
                nodeValue = (node.testScoreWhite() - node.testScoreBlack());
            }
            else
            {
                nodeValue = (node.testScoreBlack() - node.testScoreWhite());
            }
            // Store the return value, and return it.
            mini returnValue = std::make_pair(nodeValue, moveMade);
            return returnValue;
        }
    }

    // Handle non terminal nodes. Handle if the player/Ai should be maximized.
    if (maximizingPlayer)
    {
        // Setup values.
        int bestValue = -5000;
        move bestMove = std::make_pair(0, 0);
        moves allMoves = node.getLegitMoves(maximizingColor);

        // Start up new child-nodes.
        while ( !allMoves.empty() )
        {
            // Setup node values.
            move tempMove = allMoves.front(); allMoves.pop_front();
            game tempNode = node;
            tempNode.makeMove(tempMove.first, tempMove.second, maximizingColor);

            // We are maximizing the player. Test if it is the opponents turn 
            // when the move has been completed.
            if (tempNode.testPlayerTurn() == reverseColor(maximizingColor))
            {
                // Test for possible cut-off.
                if ( !(beta <= alpha) )
                {
                    // Start the new game.
                    mini tempMini = alphaBeta(
                        tempNode,        // New node.
                        depth - 1,       // New depth.
                        false,           // Opponents turn, time to minimize.
                        maximizingColor, // Maximize for the same color.
                        alpha,           // Alpha.
                        beta,            // Beta.
                        tempMove,        // The move that was made.
                        useHeuFunc);     // Use heuristic evaluation?

                    // Test if this was the best move.
                    if (tempMini.first > bestValue)
                    {
                        bestValue = tempMini.first;
                        bestMove = tempMove;
                        alpha = tempMini.first;
                    }
                }
                else
                {
                    // Alfa is bigger than or equal to beta.
                    break;
                }
            }
            // Else, if there is your turn again once the move has been made.
            else
            {
                // Test for possible cut-off.
                if ( !(beta <= alpha) )
                {
                    // Start the new game.
                    mini tempMini = alphaBeta(
                        tempNode,        // New node.
                        depth - 1,       // New depth.
                        true,            // Ai's turn again.
                        maximizingColor, // Maximize for the same color.
                        alpha,           // Alpha.
                        beta,            // Beta.
                        tempMove,        // The move that was made.
                        useHeuFunc);     // Use heuristic evaluation?

                    // Test if this was the best move.
                    if (tempMini.first > bestValue)
                    {
                        bestValue = tempMini.first;
                        bestMove = tempMove;
                        alpha = tempMini.first;
                    }
                }
                else
                {
                    // Your turn again once move is made.
                    break;
                }
            }
            
        }
        // Return the best mini.
        return makeMini(bestValue, bestMove.first, bestMove.second);
    }

    /* Else, if the AI should be minimized! */
    else
    {
        // Setup values.
        int bestValue = 5000;
        move bestMove;
        moves allMoves = node.getLegitMoves(reverseColor(maximizingColor));

        while ( !allMoves.empty() )
        {
            // Setup node values.
            move tempMove = allMoves.front(); allMoves.pop_front();
            game tempNode = node;
            tempNode.makeMove(tempMove.first, tempMove.second, reverseColor(maximizingColor));

            // Start testing children.  We are minimizing the player. Test if 
            // it is the Ai's turn when the move. has completed.
            if (tempNode.testPlayerTurn() == maximizingColor)
            {
                // Test for cut-offs.
                if ( !(beta <= alpha) )
                {
                    // Start the new game.
                    mini tempMini = alphaBeta(
                        tempNode,        // New node.
                        depth - 1,       // New depth.
                        true,            // The next move belongs to the AI.
                        maximizingColor, // Maximize for the same color.
                        alpha,           // Pass the alpha along.
                        beta,            // Pass the beta along.
                        tempMove,        // The move that was made.
                        useHeuFunc);     // Use the heuristic evaluationfunction?

                    // Test if the new node was any better.
                    if (tempMini.first < bestValue)
                    {
                        bestValue = tempMini.first;
                        bestMove = tempMove;
                        beta = tempMini.first;
                    }
                }
                else 
                {
                    break;
                }
            }
            else
            {
                // Opponents turn again.
                if ( !(beta <= alpha) )
                {
                    mini tempMini = alphaBeta(
                        tempNode,
                        depth - 1,
                        false,
                        maximizingColor,
                        alpha,
                        beta,
                        tempMove,
                        useHeuFunc
                        );

                    // Test if the new node was any better.
                    if (tempMini.first < bestValue)
                    {
                        bestValue = tempMini.first;
                        bestMove = tempMove;
                        beta = tempMini.first;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        // Inside of "minizing AI", return the best value for minimizing the ai.
        return makeMini(bestValue, bestMove.first, bestMove.second);
    }
}

// Huristic valuing function.
int ai::heuristicValue(game _game, piece maximizingColor)
{
    return mobilityTester(_game, maximizingColor) +
           cornerTester(_game, maximizingColor) +
           fieldTester(_game, maximizingColor);

}

// The mobility tester function. It is benifitial to have many move and to
// restrict the amount of possible moves for the opponent.
int ai::mobilityTester(game _game, piece maximizingColor)
{
    // This function will return a value between 16 and -16 depending on how
    // many moves the maximizing color has above the minimizing color. 
    piece minimizingColor = reverseColor(maximizingColor);
    float maxValue = _game.getLegitMoves(maximizingColor).size();
    float minValue = _game.getLegitMoves(minimizingColor).size();

    if (minValue == 0)
    {
        // Opponent can't make any moves.
        return 16;
    }
    else if (maxValue == 0)
    {
        // User can't make any moves.
        return -16;
    }
    else
    {
        // Weight values.
        int returnValue = 16 * ((maxValue - minValue) / (maxValue + minValue));
        return returnValue;
    }
}

// The corener tester function. Returns a value based on how many corner the ai
// have vs how many the opponent have.
int ai::cornerTester(game _game, piece maximizingColor)
{
    // Corner weight.
    constexpr int WEIGHT = 40;

    // This funciton will return the value of a game depending on who has the 
    // corners. It will give the heuristic value of 40 for each own corner.
    int maxCorners{}, minCorners{};
    piece minimizingColor = reverseColor(maximizingColor);

    const std::pair<int, int> corner[4] {
        { 0, 0 }, { 0, 7 }, { 7, 0 }, { 7, 7 }
    };
    for (auto &&pair : corner)
    {
        // Maximizing and minimizing color tests.
        int a = pair.first, b = pair.second;
        if (_game.testTile(a, b) == maximizingColor) maxCorners++;
        if (_game.testTile(a, b) == minimizingColor) minCorners++;
    }

    // Add the heuristic Value (40) to the corners.
    maxCorners = maxCorners * WEIGHT;
    minCorners = minCorners * WEIGHT;
    return maxCorners - minCorners;
}

int ai::fieldTester(game _game, piece maximizingColor)
{
    // This function returns the amount of tiles that a player holds over the
    // opponent.
    int returnValue{};
    for (unsigned x = 0; x < 8; x++) 
    {
        for (unsigned y = 0; y < 8; y++)
        {
            if (_game.testTile(x, y) != piece::EMPTY)
            {
                // Tile isn't empty.
                returnValue += tileWeight(x, y, _game, maximizingColor);
            }
        }
    }

    //Reutrn the return value.
    return returnValue;
}

// Give certain tiles some extra weight.
int ai::tileWeight(unsigned x, unsigned y, game _game, piece maximizingColor)
{
    // Tile weight function for give some tiles extra weight. This function does
    // not perform weights on the sharp corners.
    constexpr int WIDTH = 8, HEIGHT = 8;
    constexpr int weights[HEIGHT][WIDTH] = {
        {  0, -2,  2,  2,  2,  2, -2,  0 },
        { -2, -3,  1,  1,  1,  1, -3, -2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        {  2,  1,  1,  1,  1,  1,  1,  2 },
        { -2, -3,  1,  1,  1,  1, -3, -2 },
        {  0, -2,  2,  2,  2,  2, -2,  0 }
    };

    // Return the propriate value
    piece tile = _game.testTile(x, y);
    if (tile == piece::EMPTY)
    {
        return 0;
    }
    else if (tile == maximizingColor)
    {
        return weights[y][x];
    }
    else
    {
        return -weights[y][x];
    }
}

// Reverse color method.
piece ai::reverseColor(piece color) const
{
    if (color == piece::WHITE)
    {
        return piece::BLACK;
    }
    else if (color == piece::BLACK)
    {
        return piece::WHITE;
    }
    else
    {
        return piece::BADPICE;
    }
}

// Help function for making a mini.
mini ai::makeMini(int value, unsigned x, unsigned y) const
{
    return { value, { x, y } };
}

// Set current game method. This method is used to change the game that
// the ai holds.
void ai::setCurrentGame(game newGame)
{
    _currentGame = newGame;
}

// Method for setting the color the the AI plays for.
void ai::setAiColor(piece color)
{
    _aiColor = color;
}

// Method for getting the AI's color.
piece ai::getAiColor() const
{
    return _aiColor;
}

// Internal method used by the ai to get the searchdepth for each turn.
int ai::getSearchDepth()
{
    // Shorten the search depth if there are overwhelming many moves available.
    int moveCount = _currentGame.getLegitMoves(_aiColor).size();
    return moveCount <= 7 ? _searchDepth : _searchDepth - 1;
}

// Set the searchdepth.
void ai::setSearchDepth(unsigned int searchDepth)
{
    _searchDepth = searchDepth;
}
