#pragma once
#include "pMove.h"
#include <vector>
using namespace std;
class Chess
{
public:
	Chess();//보드 생성
	~Chess();
	char isOver(char** board);
	void Play();
	void printBoard(char** board);
	pMove Move(int depth);
	int MoveRecursive(char** board, int depth);
	char** getBoard();
	void setBoard(char** board, char** temboard);
	vector<pMove> RookMove(char** board, bool isComputer, int x, int y);
	vector<pMove> KnightMove(char** board, bool isComputer, int x, int y);
	vector<pMove> BishopMove(char** board, bool isComputer, int x, int y);
	int getPoint(char a);
	int getNegativePoint(char a);
	vector<pMove> KingMove(char** board, bool isComputer, int x, int y);
	vector<pMove> QueenMove(char** board, bool isComputer, int x, int y);
	vector<pMove> PawnsMove(char** board, bool isComputer, int x, int y);
private:
	char** board;
};

