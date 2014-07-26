#include "Minimax.h"

void Minimax::createMinimaxWithAB(Board & input)
{
	int value;
	//cout << "start Minimax::createMinimaxWithAB"<<endl;
	value=MaxAB(input,DEPTH,-INFINITE,INFINITE);
	//cout <<endl<< "end Minimax::createMinimaxWithAB"<<value<<endl;
}

int Minimax::MaxAB(Board & inputBoard,const int & depth, int alpha, int beta)
{
	if (inputBoard.checkWin() || inputBoard.isBoardFull()|| depth <= 0)
	{
		int h=inputBoard.getHeuristic();
		//cout << "; h = "<<h;
		outputFile << "; h="<<h;
		return h;
	}
	for (int i=0;i<inputBoard.numberOfColumns();i++)
	{
		if(inputBoard.addChip(i,'a'))
		{
			if (depth!=DEPTH)
				tabString+=SPACING;
			//cout<<endl<<tabString<<"A"<<DEPTH-depth+1<<": "<<i+1;
			if (!firstLine)
				outputFile<<endl<<tabString<<"A"<<DEPTH-depth+1<<": "<<i+1;
			else
			{
				outputFile<<tabString<<"A"<<DEPTH-depth+1<<": "<<i+1;
				firstLine=false;
			}
			int previousAlpha=alpha;
			
			alpha=max(alpha,MinAB(inputBoard,depth-1,alpha,beta));
			if (previousAlpha!=alpha && depth==DEPTH)
			{
				bestMove=i+1;
				//cout <<"bestMove"<<bestMove<<"previousAlpha" <<previousAlpha<<"alpha "<<alpha <<endl;
			}
			inputBoard.popChip(i);
			if (i+1 < inputBoard.numberOfColumns() && alpha>=beta)
			{
				//cout<<endl<<tabString<<"A"<<DEPTH-depth+1<<": ";
				//cout<<"Pruning ";
				outputFile<<endl<<tabString<<"A"<<DEPTH-depth+1<<": ";
				outputFile<<"pruning ";
				for (int j=i+1;j<inputBoard.numberOfColumns();j++)
				{
					if (inputBoard.addChip(j,'a'))
					{
						inputBoard.popChip(j);
						//cout<<j+1<<", ";
						outputFile<<j+1;
						if (j==inputBoard.numberOfColumns()-1)
							outputFile <<"; ";
						else
							outputFile <<", ";
					}
				}
				//cout<<"alpha= "<< alpha<<" beta="<<beta;
				outputFile<<"alpha="<< alpha<<", beta="<<beta;
				if (depth!=DEPTH)
					tabString.resize(tabString.size()-2);
				return beta;
			}
			if (depth!=DEPTH)
				tabString.resize(tabString.size()-2);
		}
	}
	return alpha;
}

int Minimax::MinAB(Board & inputBoard,const int & depth , int alpha, int beta)
{
	
	if (inputBoard.checkWin() || inputBoard.isBoardFull() || depth <= 0)
	{
		int h=inputBoard.getHeuristic();
		//cout << "; h = "<<h;
		outputFile << "; h="<<h;
		return h;
	}
	for (int i=0;i<inputBoard.numberOfColumns();i++)
	{
		if (inputBoard.addChip(i,'b'))
		{
			if (depth!=4)
				tabString+=SPACING;
			//cout<<endl<<tabString<<"B"<<DEPTH-depth+1<<": "<<i+1;
			if (!firstLine)
				outputFile << endl<<tabString<<"B"<<DEPTH-depth+1<<": "<<i+1;
			else 
			{
				outputFile << tabString<<"B"<<DEPTH-depth+1<<": "<<i+1;
				firstLine=false;
			}
			beta=min(beta,MaxAB(inputBoard,depth-1,alpha,beta));
			inputBoard.popChip(i);
			if (i+1 < inputBoard.numberOfColumns() && beta<= alpha)
			{
				//cout<<endl<<tabString<<"B"<<DEPTH-depth+1<<": ";
				//cout<<"Pruning ";
				outputFile<<endl<<tabString<<"B"<<DEPTH-depth+1<<": ";
				outputFile<<"pruning ";
				for (int j=i+1;j<inputBoard.numberOfColumns();j++)
				{
					if (inputBoard.addChip(j,'a'))
					{
						inputBoard.popChip(j);
						//cout<<j+1<<", ";
						outputFile <<j+1;
						if (j==inputBoard.numberOfColumns()-1)
							outputFile <<"; ";
						else
							outputFile <<", ";
					}
				}
				//cout<<"alpha= "<< alpha<<" beta="<<beta;
				outputFile<<"alpha="<< alpha<<", beta="<<beta;
				if (depth!=4)
					tabString.resize(tabString.size()-2);
				return alpha;
			}
			if (depth!=4)
				tabString.resize(tabString.size()-2);
		}
	}
	
	return beta;
}

Minimax::Minimax(char * outputFileName) : outputFile(outputFileName),firstLine(true)
{
	if (!outputFile)
	{
		cerr<<"Could not open output file"<<outputFileName<<endl;
		exit(1);
	}
}

Minimax::~Minimax()
{
	outputFile<<endl;
	outputFile<<"first move: "<<bestMove;
	outputFile.close();
}
