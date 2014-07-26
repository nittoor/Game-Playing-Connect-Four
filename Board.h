#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

const int NUMBER_OF_COLUMNS = 7;
const int NUMBER_OF_ROWS =6;

const string BLANK2TWOA = " aa" ;
const string TWOABLANK = "aa " ;
const string BLANKTHREEA = " aaa" ;
const string THREEABLANK = "aaa " ;
const string BLANK2TWOB = " bb" ;
const string TWOBBLANK = "bb " ;
const string BLANKTHREEB = " bbb" ;
const string THREEBBLANK = "bbb " ;
const string FOURA = "aaaa";
const string FOURB = "bbbb";

typedef vector<char> BoardColumn;
typedef vector<BoardColumn> GameBoard;

class Board
{
public:
	Board(const vector<string> & inputBoard);
	void printBoard();
	int getHeuristic();
	bool isBoardFull();
	int checkWin();
	bool addChip(int col,char turn);
	bool popChip(int col);
	inline int numberOfColumns() const {return NUMBER_OF_COLUMNS;};
	~Board();

private:
	Board();
	void rowWiseHeuristic();
	void colWiseHeuristic();
	void topDiagonalWiseHeuristic(); // " \ "
	void botDiagonalWiseHeuristic(); // " / "
	GameBoard BoardState;
	vector<string> verificationStrings;
	map<string,int> verificationStringsCountMap;

};
