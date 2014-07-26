#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Minimax.h"

using namespace std;

const int FILE_NAME_SIZE=100;

int main (int argc, char * argv [])
{
	char inputFileName[FILE_NAME_SIZE];
	char outputFileName[FILE_NAME_SIZE];
	if (argc!=3)
	{
		cerr<<"Usage : executable_name <input file> <output file>";
		exit(1);
	}

	strcpy(inputFileName,argv[1]);
	strcpy(outputFileName,argv[2]);

	ifstream inputFile(inputFileName);
	if (!inputFile)
	{
		cerr<<"Could not open inpue file"<<inputFileName<<endl;
		exit(1);
	}
	
	vector<string> inputBoard;
	string inputLine;
	while (getline(inputFile,inputLine))
	{
		//cout<<"input line="<<inputLine<<endl;
		inputBoard.push_back(inputLine);
	}

	Board NewInputBoard(inputBoard);
	//NewInputBoard.printBoard();
	//cout << "h "<<NewInputBoard.getHeuristic()<<endl;
	Minimax MinimaxWithAB(outputFileName);
	MinimaxWithAB.createMinimaxWithAB(NewInputBoard);

	return 0;
}
