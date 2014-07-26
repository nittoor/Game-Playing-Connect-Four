#include "Board.h"

Board::Board(const vector<string> & inputBoard)
{
	if (inputBoard.size()!=NUMBER_OF_COLUMNS)
	{
		cerr<<"Wrong number of columns in input borad!!"<<endl;
		exit(1);
	}
	BoardState.resize(NUMBER_OF_COLUMNS);
	for (int i=0;i<NUMBER_OF_COLUMNS;i++)
	{
		if (inputBoard[i].size()>NUMBER_OF_ROWS)
		{
		cerr<<"Wrong number of rows in input borad!!"<<endl;
		exit(1);
		}
		BoardState[i].resize(NUMBER_OF_ROWS,' ');
		for (int j=0;j<inputBoard[i].size();j++)
		{
			if (inputBoard[i][j]!='e')
			BoardState[i][j]=inputBoard[i][j];
		}
	}

	verificationStrings.push_back(BLANK2TWOA);
	verificationStrings.push_back(TWOABLANK);
	verificationStrings.push_back(BLANKTHREEA);
	verificationStrings.push_back(THREEABLANK);
	verificationStrings.push_back(BLANK2TWOB);
	verificationStrings.push_back(TWOBBLANK);
	verificationStrings.push_back(BLANKTHREEB);
	verificationStrings.push_back(THREEBBLANK);
	verificationStrings.push_back(FOURA);
	verificationStrings.push_back(FOURB);
	for (int i=0;i<verificationStrings.size();i++)
		verificationStringsCountMap.insert(pair<string,int>(verificationStrings[i],0));
}

void Board::printBoard()
{
	cout<<"================================"<<endl;
	for (int i=0;i<NUMBER_OF_COLUMNS;i++)
	{
		for (int j=0;j<NUMBER_OF_ROWS;j++)
		{
			cout<<BoardState[i][j];
		}
		cout<<endl;
	}
	cout<<"================================"<<endl;
	
}

bool Board::isBoardFull()
{
	for (int i=0;i<NUMBER_OF_COLUMNS;i++)
	{
		for (int j=0;j<NUMBER_OF_ROWS;j++)
		{
		if (BoardState[i][j]==' ')
			return false;
		}
	}
	return true;
}

bool Board::addChip(int col,char turn)
{
	for (int j=0;j<NUMBER_OF_ROWS;j++)
		{
			if (BoardState[col][j]==' ')
			{
				BoardState[col][j]=turn;
				return true;
			}
		}
	return false;
}

bool Board::popChip(int col)
{
	for (int j=0;j<NUMBER_OF_ROWS;j++)
		{
			if (BoardState[col][j]==' ')
			{
				BoardState[col][j-1]=' ';
				return true;
			}
		}
	BoardState[col][NUMBER_OF_ROWS-1]=' ';
}

int Board::getHeuristic()
{
	if (checkWin())
	{
		return checkWin();
	}

	else if (isBoardFull() && !checkWin())
	{
		return 0;
	}
	
	else 
	{
		for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
			i->second=0;

		rowWiseHeuristic();
		colWiseHeuristic();
		topDiagonalWiseHeuristic();
		botDiagonalWiseHeuristic();
		//printBoard();
	
	
	if (verificationStringsCountMap[BLANKTHREEA]!=0)
		verificationStringsCountMap[BLANK2TWOA]-=verificationStringsCountMap[BLANKTHREEA];
	if (verificationStringsCountMap[THREEABLANK]!=0)
		verificationStringsCountMap[TWOABLANK]-=verificationStringsCountMap[THREEABLANK];
	
	if (verificationStringsCountMap[BLANKTHREEB]!=0)
		verificationStringsCountMap[BLANK2TWOB]-=verificationStringsCountMap[BLANKTHREEB];
	if (verificationStringsCountMap[THREEBBLANK]!=0)
		verificationStringsCountMap[TWOBBLANK]-=verificationStringsCountMap[THREEBBLANK];
	
	//for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
	//	cout<<i->first <<"=" <<i->second<<endl;

	return ((verificationStringsCountMap[BLANK2TWOA]+verificationStringsCountMap[TWOABLANK]-verificationStringsCountMap[BLANK2TWOB]-verificationStringsCountMap[TWOBBLANK])
			+(verificationStringsCountMap[BLANKTHREEA]+verificationStringsCountMap[THREEABLANK]-verificationStringsCountMap[BLANKTHREEB]-verificationStringsCountMap[THREEBBLANK])*5);
	}
}

int Board::checkWin()
{
	for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
			i->second=0;
	rowWiseHeuristic();
	colWiseHeuristic();
	topDiagonalWiseHeuristic();
	botDiagonalWiseHeuristic();
	if(verificationStringsCountMap[FOURA]!=0 )
		return 1000;
	if (verificationStringsCountMap[FOURB]!=0)
		return -1000;
	else 
		return 0;
}

void Board::colWiseHeuristic()
{
	string tempString;
	for (int i=0;i<NUMBER_OF_COLUMNS;i++)
	{
		//cout<<endl;
		for (int j=0;j<NUMBER_OF_ROWS;j++)
		{
			//std::cout << i <<j << " " <<BoardState[i][j] << "\t";
			tempString+=BoardState[i][j];
		}
		

		//std::cout<<tempString<<endl;

		for (int x=0;x<verificationStrings.size();x++)
		{
			if (tempString.find(verificationStrings[x])!=std::string::npos)
			{
				verificationStringsCountMap[verificationStrings[x]]++;
			}
		}

		tempString.erase();
	}
	/*
	cout << "colWise" <<endl ;
	for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
		cout<<i->first <<"=" <<i->second<<endl;
		*/
}

void Board::rowWiseHeuristic()
{
	string tempString;
	for (int j=0;j<NUMBER_OF_ROWS;j++)
	{
		//cout<<endl;
		for (int i=0;i<NUMBER_OF_COLUMNS;i++)
		{
			//std::cout << i <<j << " " <<BoardState[i][j] << "\t";
			tempString+=BoardState[i][j];
		}

		//std::cout<<tempString<<endl;

		for (int x=0;x<verificationStrings.size();x++)
		{
			if (tempString.find(verificationStrings[x])!=std::string::npos)
			{
				verificationStringsCountMap[verificationStrings[x]]++;
			}
		}

		tempString.erase();
	}
	/*
	cout << "rowWise" <<endl ;
	for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
		cout<<i->first <<"=" <<i->second<<endl;
		*/
}

void Board::topDiagonalWiseHeuristic()
{
	int i,j;
	int rowIndex,colIndex;
	string tempString;
	
	for (rowIndex=NUMBER_OF_COLUMNS-3,colIndex=0;colIndex<NUMBER_OF_ROWS-2;)
	{
		//std::cout<<"\nrowindex="<<rowIndex<< " Colindex="<<colIndex<<endl;
		for ( i=rowIndex,j=colIndex;i<NUMBER_OF_COLUMNS && j<NUMBER_OF_ROWS ;i++,j++)
		{
			//std::cout << i <<j << " " <<BoardState[i][j] << "\t";
			tempString+=BoardState[i][j];
		}
		if (--rowIndex <0 )
		{
			rowIndex =0;
			colIndex=colIndex++;
		}
		//std::cout<<tempString<<endl;

		for (int x=0;x<verificationStrings.size();x++)
		{
			if (tempString.find(verificationStrings[x])!=std::string::npos)
			{
				verificationStringsCountMap[verificationStrings[x]]++;
			}
		}

		tempString.erase();
	}
	/*
	std::cout << "topDiagWise"<<endl;
	for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
		cout<<i->first <<"=" <<i->second<<endl;
	*/
}

void Board::botDiagonalWiseHeuristic()
{
	
	int i,j;
	int rowIndex,colIndex;
	string tempString;
	
	for (rowIndex=2,colIndex=0;colIndex<NUMBER_OF_ROWS-2;)
	{
		for ( i=rowIndex,j=colIndex;i>=0 && j<NUMBER_OF_ROWS;i--,j++)
		{
			//std::cout << i <<j << " " <<BoardState[i][j] << "\t";
			tempString+=BoardState[i][j];
		}
		//std::cout<<tempString<<endl;
			
		if (++rowIndex >NUMBER_OF_COLUMNS-1 )
		{
			rowIndex =NUMBER_OF_COLUMNS -1;
			colIndex=colIndex++;
		}
		for (int x=0;x<verificationStrings.size();x++)
		{
			if (tempString.find(verificationStrings[x])!=std::string::npos)
			{
				verificationStringsCountMap[verificationStrings[x]]++;
			}
		}

		tempString.erase();
	}
	/*
	cout << "botDiagWise" <<endl ;
	for (map<string,int>::iterator i=verificationStringsCountMap.begin();i!=verificationStringsCountMap.end();i++)
		cout<<i->first <<"=" <<i->second<<endl;
	*/
}


Board::Board()
{
}

Board::~Board()
{
}
