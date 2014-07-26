#include <iostream>
#include "Board.h"
#include <string.h>
#include <fstream>

const int INFINITE=2000;
const int DEPTH=4;
const string SPACING = "|-";

class Minimax
{
public:
	Minimax(char * );
	~Minimax();
	void createMinimaxWithAB( Board &);
private:
	string tabString;
	int MaxAB( Board & ,const int & depth,int alpha,int beta);
	int MinAB( Board & ,const int & depth,int alpha, int beta);
	ofstream outputFile;
	int bestMove;
	bool firstLine;
};
