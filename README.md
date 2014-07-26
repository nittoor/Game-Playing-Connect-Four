Game-Playing-Connect-Four
=========================

Suppose Alice is playing Connect Four against Bill. Given a current game configuration,
you will help Alice to determine the next move that will maximize her chance of winning.
You will use minimax algorithm with alpha-beta pruning to calculate the optimal move.

Connect Four: http://en.wikipedia.org/wiki/Connect_Four

Alice and Bill are playing the game, and it is Alice’s turn to take next move. 
Then program will take the current board configuration as input.
The input file path will be given as a command-line
parameter (see grading). The input will always be valid. For example (input.txt):

e

abba

baa

e

abbaab

ab

b

This input is “rotated sideways” to make scanning it easier. In other words, each line of
text corresponds to a column in the grid. The first line represents the left-most column.
The interpretations are
‘e’ denotes an empty column.
‘a’ denotes Alice’s piece.
‘b’ denotes Bill’s piece.

using minimax algorithm with alpha-beta pruning to determine Alice’s
next move that yields the best utility for her. For simplicity, you only need to
consider all possible states for the next 4 moves.


Your heuristic function will be defined as follows:
· If Alice has won, the value is 1000.
· If Alice has lost, the value is -1000.
· If the game is a draw, the value is 0.
· Otherwise, the value is (xA - xB) + 5 * (yA - yB), where
· xA and xB are the number of unterminated lines of length 2 for Alice and Bill
· yA and yB are the number of unterminated lines of length 3 for Alice and Bill
· By unterminated line, we mean a certain number of pieces of a single player are
in a row, and there is a free space on at least one side of the line (i.e. it is still
possible for this line to be part of a winning line).


The output of your program will be the next optimal move for Alice, along with a
printout of your minimax tree. It is achieved by traversing all possible search states for
the next 4 moves using minimax algorithm with alpha-beta pruning. Below is a sample
output, but is just an arbitrary example and is not necessarily correct (in fact, most of
the time there will be 7 actions, one for each column):

A1: 2

|-B2: 2

|-|-A3: 1

|-|-|-B4: 2; h=0

|-|-|-B4: 3; h=5

|-|-A3: 3

|-|-|-B4: 4; h=0

|-|-A3: pruning 4, 5, 6, 7; alpha=1, beta=1

|-B2: 3; h = 1000

A1: 3

...

first move: 3

The interpretations are:
1. The output will be the traversal of possible search states, but not the optimal search
path. Each move could be followed by several possible moves, we use “|-“ to
represent the traversal relationships of the two consecutive moves.
2. Each line is in the format of “Pi: c”, where P could be A (Alice) or B (Bill), i=1,
2, 3 or 4 denoting the following ith move, c is the column number (1-7, 1 being
the leftmost column).
3. If it is the 4th move, please output heuristic value after (e.g., B4: 7; h=5).
4. If the move involves alpha-beta pruning, please output all branch moves that should
be pruned and the values of alpha and beta, e.g., pruning 4, 5, 6, 7; alpha=1,
beta=1
5. After traversing all possible states, output the answer of Alice’s first move, e.g., first
move: 1
