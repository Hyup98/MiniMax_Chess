#include "Chess.h"
#include <iostream>
#include<vector>
using namespace std;

//   abcdefgh
//  +--------+
//0 |RN KQBNR|
//1 |P PPPPPP|
//2 |P       |
//3 |        |
//4 |p       |
//5 |p       |
//6 |pp pbp  |
//7 |rnbkq nr|
//  +--------+

Chess::Chess()
{
	board = new char*[8];
	for (size_t i = 0; i < 8; i++)
	{
		board[i] = new char[8];
	}

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{

			if (i == 1)
			{
				board[i][j] = 'P';
			}
			else if (i == 6)
			{
				board[i][j] = 'p';
			}
			else if (i == 0)
			{
				if (j == 0 || j == 7)
				{
					board[i][j] = 'R';
				}
				else if (j == 1 || j == 6)
				{
					board[i][j] = 'N';
				}
				else if (j == 2 || j == 5)
				{
					board[i][j] = 'B';
				}
				else if (j == 3)
				{
					board[i][j] = 'K';
				}
				else 
				{
					board[i][j] = 'Q';
				}
			}
			else if (i == 7)
			{
				if (j == 0 || j == 7)
				{
					board[i][j] = 'r';
				}
				else if (j == 1 || j == 6)
				{
					board[i][j] = 'n';
				}
				else if (j == 2 || j == 5)
				{
					board[i][j] = 'b';
				}
				else if (j == 3)
				{
					board[i][j] = 'k';
				}
				else
				{
					board[i][j] = 'q';
				}
			}
			else 
			{
				board[i][j] = ' ';
			}
		}
	}
}

Chess::~Chess()
{
	for (size_t i = 0; i < 8; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

//유저 대문자
//컴퓨터 소문자
//C - computer
//U - user
//P - Proceeding
char Chess::isOver(char** board)
{
	//체크 메이트인 경우
	//말이 하나도 없을 경우
	bool hasK = false;
	bool hask = false;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (board[i][j] == 'K')
			{
				hasK = true;
			}
			else if (board[i][j] == 'k')
			{
				hask = true;
			}
			if (hask == true && hasK == true)
			{
				break;
			}
		}
		if (hask == true && hasK == true)
		{
			break;
		}
	}
	if (hasK == false)
	{
		return'C';
	}
	else if (hask == false)
	{
		return 'U';
	}
	return 'P';
}

void Chess::Play()
{
	cout << "*******WELLCOME*******\n";
	printBoard(getBoard());
	int count = 1;
	int fromX, fromY,toX,toY;
	pMove move;

	while (true)
	{
		if (isOver(board) == 'C')
		{
			cout << "Computer victory";
			break;
		}
		else if (isOver(board) == 'U')
		{
			cout << "User victory";
			break;
		}
		//컴퓨터 - 홀수 번째
		if (count % 2 == 1)
		{
			move = Move(0);
			board[move.mToX][move.mToY] = board[move.mFromX][move.mFromY];
			board[move.mFromX][move.mFromY] = ' ';
		}
		//유저 - 짝수 번쨰
		else
		{
			cout << "Move from : ";
			cin >> fromX;
			cin >> fromY;
			cout << "\nMove to: ";
			cin >> toX;
			cin >> toY;
			board[toX][toY] = board[fromX][fromY];
			board[fromX][fromY] = ' ';
		}
		count++;
		printBoard(board);
	}
}

void Chess::printBoard(char** board)
{
	cout << "   abcdefgh\n";
	cout << "  +--------+\n";
	for (size_t i = 0; i < 8; i++)
	{
		cout << i << " |";
		for (size_t j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << "|\n";
	}
	cout << "  +--------+\n\n";
}

void Chess::setBoard(char** board, char** temboard)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			temboard[i][j] = board[i][j];
		}
	}
}

pMove Chess::Move(int depth)
{
	//컴퓨터는 소문자이다
	//둘 수 있는 모든 수를 자식으로 만든다
	vector<pMove> tem;
	vector<pMove> save;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (board[i][j] != ' ' && board[i][j] >= 'a' && board[i][j] <= 'z')
			{
				//그 말이 갈 수 있는 곳을 모두 자식으로 저장
				switch (board[i][j])
				{
				case 'r':
					save = RookMove(board, true, i, j);
					break;
				case 'n':
					save = KnightMove(board, true, i, j);
					break;
				case 'b':
					save = BishopMove(board, true, i, j);
					break;
				case 'k':
					save = KingMove(board, true, i, j);
					break;
				case 'q':
					save = QueenMove(board, true, i, j);
					break;
				case 'p':
					save = PawnsMove(board, true, i, j);
					break;
				}

				for (size_t k = 0; k < save.size(); k++)
				{
					tem.push_back(save[k]);
				}
				save.clear();
			}
		}
	}
	//모든 자식을 재귀함수를 호출하여 각 점수를 매긴다
	for (size_t i = 0; i < tem.size(); i++)
	{
		//움직인 곳으로 말을 둔 보드를 생성
		char** temboard = new char* [8];
		for (size_t j = 0; j < 8; j++)
		{
			temboard[j] = new char[8];
		}
		setBoard(board, temboard);

		temboard[tem[i].mToX][tem[i].mToY] = temboard[tem[i].mFromX][tem[i].mFromY];
		temboard[tem[i].mFromX][tem[i].mFromY] = ' ';
		//그 보드를 매개변수로 받는 move재귀함수를 호출
		//반환값인 평가값을 저장
		tem[i].addPoint(MoveRecursive(temboard, depth + 1));
		//보드 삭제
		for (size_t j = 0; j < 8; j++)
		{
			delete[] temboard[j];
		}
		delete[] temboard;
	}

	//점수중 가장 큰 값을 가진 자식을 반환한다,
	int max = tem[0].mPoint;
	int index = 0;
	for (size_t i = 0; i < tem.size(); i++)
	{
		if (tem[i].mPoint > max)
		{
			max = tem[i].mPoint;
			index = i;
		}
	}
	return tem[index];
}

int Chess::MoveRecursive(char** board, int depth)
{
	int a = 0;
	if (depth == 5)
	{
		return 0;
	}
	for (int i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (board[i][j] == 'k' || board[i][j] == 'K')
			{
				a++;
			}
		}
	}
	if (a != 2)
	{
		return 0;
	}
	//둘 수 있는 모든 수를 자식으로 만든다
	//유저가 두는 경우 대문자가 움직인다
	vector<pMove> tem;
	vector<pMove> save;
	if (depth % 2 == 1)
	{
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				if (board[i][j] != ' ' && board[i][j] >= 'A' && board[i][j] <= 'Z')
				{
					//그 말이 갈 수 있는 곳을 모두 자식으로 저장
					switch (board[i][j])
					{
					case 'R':
						save = RookMove(board, false, i, j);
						break;
					case 'N':
						save = KnightMove(board, false, i, j);
						break;
					case 'B':
						save = BishopMove(board, false, i, j);
						break;
					case 'K':
						save = KingMove(board, false, i, j);
						break;
					case 'Q':
						save = QueenMove(board, false, i, j);
						break;
					case 'P':
						save = PawnsMove(board, false, i, j);
						break;
					}

					for (size_t k = 0; k < save.size(); k++)
					{
						tem.push_back(save[k]);
					}
					save.clear();
				}
			}
		}
	}
	//컴퓨터가 두는 경우  소문자가 움직인다.
	else
	{
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				if (board[i][j] != ' ' && board[i][j] >= 'a' && board[i][j] <= 'z')
				{
					//그 말이 갈 수 있는 곳을 모두 자식으로 저장
					switch (board[i][j])
					{
					case 'r':
						save = RookMove(board, true, i, j);
						break;
					case 'n':
						save = KnightMove(board, true, i, j);
						break;
					case 'b':
						save = BishopMove(board, true, i, j);
						break;
					case 'k':
						save = KingMove(board, true, i, j);
						break;
					case 'q':
						save = QueenMove(board, true, i, j);
						break;
					case 'p':
						save = PawnsMove(board, true, i, j);
						break;
					}

					for (size_t k = 0; k < save.size(); k++)
					{
						tem.push_back(save[k]);
					}
					save.clear();
				}
			}
		}
	}

	if (tem.size() == 0)
	{
		return 0;
	}

	//최솟값 반환
	if (depth % 2 == 1)
	{
		//모든 자식을 재귀함수를 호출하여 각 점수를 매긴다
		for (size_t i = 0; i < tem.size(); i++)
		{
			//움직인 곳으로 말을 둔 보드를 생성
			char** temboard = new char* [8];
			for (size_t j = 0; j < 8; j++)
			{
				temboard[j] = new char[8];
			}
			setBoard(board, temboard);

			temboard[tem[i].mToX][tem[i].mToY] = temboard[tem[i].mFromX][tem[i].mFromY];
			temboard[tem[i].mFromX][tem[i].mFromY] = ' ';
			//그 보드를 매개변수로 받는 move재귀함수를 호출
			//반환값인 평가값을 저장
			tem[i].addPoint(MoveRecursive(temboard, depth + 1));
			//보드 삭제
			for (size_t j = 0; j < 8; j++)
			{
				delete[] temboard[j];
			}
			delete[] temboard;
		}

		//점수중 가장 작은 값을 가진 자식을 반환한다,
		int min = tem[0].mPoint;
		int index = 0;
		for (size_t i = 0; i < tem.size(); i++)
		{
			if (tem[i].mPoint < min)
			{
				min = tem[i].mPoint;
				index = i;
			}
		}
		return tem[index].mPoint;
	}
	//최댓값 반환
	else
	{
		//모든 자식을 재귀함수를 호출하여 각 점수를 매긴다
		for (size_t i = 0; i < tem.size(); i++)
		{
			//움직인 곳으로 말을 둔 보드를 생성
			char** temboard = new char* [8];
			for (size_t j = 0; j < 8; j++)
			{
				temboard[j] = new char[8];
			}
			setBoard(board, temboard);

			temboard[tem[i].mToX][tem[i].mToY] = temboard[tem[i].mFromX][tem[i].mFromY];
			temboard[tem[i].mFromX][tem[i].mFromY] = ' ';
			//그 보드를 매개변수로 받는 move재귀함수를 호출
			//반환값인 평가값을 저장
			tem[i].addPoint(MoveRecursive(temboard, depth + 1));
			//보드 삭제
			for (size_t j = 0; j < 8; j++)
			{
				delete[] temboard[j];
			}
			delete[] temboard;
		}

		//점수중 가장 큰 값을 가진 자식을 반환한다,
		int max = tem[0].mPoint;
		int index = 0;
		for (size_t i = 0; i < tem.size(); i++)
		{
			if (tem[i].mPoint > max)
			{
				max = tem[i].mPoint;
				index = i;
			}
		}
		return tem[index].mPoint;
	}
}

char** Chess::getBoard()
{
	return board;
}

/*
* 가중치
* 폰 : 10
* 나이트 : 30
* 비숍 : 30
* 룩 : 50
* 퀸 : 90
* 킹 : 900
*/
//비정적 멤버 참조는 특정 개체에 상대적이어야합니다
 int Chess::getPoint(char a)
{
	if (a == 'p' || a == 'P')
	{
		return 10;
	}
	else if (a == 'R' || a == 'r')
	{
		return 50;
	}
	else if (a == 'b' || a == 'B')
	{
		return 30;
	}
	else if (a == 'k' || a == 'K')
	{
		return 30;
	}
	else if (a == 'Q' || a == 'q')
	{
		return 90;
	}
	else
	{
		return 900;
	}
}

//   abcdefgh
//  +--------+
//0 |RN KQBNR|
//1 |P PPPPPP|
//2 |P       |
//3 |        |
//4 |p       |
//5 |p       |
//6 |pp pbp  |
//7 |rnbkq nr|
//  +--------+
//컴퓨터는 소문자
//유저는 대문자
vector<pMove> Chess::RookMove(char** board, bool isComputer,int x, int y)
{
	vector<pMove> tem;
	//
	int index;
	//컴퓨터는 소문자
	if (isComputer)
	{
		//위로
		index = x;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				break;
			}
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//아래
		index = x;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				break;
			}
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//오른쪽
		index = y;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				break;
			}
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				tem.push_back(pMove(x, y, x, index, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//왼쪽
		index = y;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				break;
			}
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
	}
	//유저 대문자
	else
	{
		//위로
		index = x;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				break;
			}
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//아래
		index = x;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				break;
			}
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//오른쪽
		index = y;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				break;
			}
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				tem.push_back(pMove(x, y, x, index, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//왼쪽
		index = y;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				break;
			}
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
	}
	return tem;
}
vector<pMove> Chess::KnightMove(char** board, bool isComputer, int x, int y)
{
	vector<pMove> tem;
	if (isComputer)
	{
		//총 경우의 수 8가지
		//2,-1
		if (x + 2 < 8 && y - 1 >= 0)
		{
			//적 말인 경우
			if (board[x + 2][y - 1] >='A' && board[x + 2][y - 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 2, y - 1, Chess::getPoint(board[x + 2][y - 1])));
			}
			else if (board[x + 2][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 2, y - 1));
			}
		}
		//2,1
		if (x + 2 < 8 && y + 1 < 8)
		{
			//적 말인 경우
			if (board[x + 2][y + 1] >= 'A' && board[x + 2][y + 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 2, y + 1, Chess::getPoint(board[x + 2][y + 1])));
			}
			else if (board[x + 2][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 2, y + 1));
			}
		}
		//1, -2
		if (x + 1 < 8 && y - 2 >= 0)
		{
			//적 말인 경우
			if (board[x + 1][y - 2] >= 'A' && board[x + 1][y - 2] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 1, y - 2, Chess::getPoint(board[x + 1][y - 2])));
			}
			else if (board[x + 1][y - 2] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y - 2));
			}
		}
		//1,2
		if (x + 1 < 8 && y + 2 < 8)
		{
			//적 말인 경우
			if (board[x + 1][y + 2] >= 'A' && board[x + 1][y + 2] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 1, y + 2, Chess::getPoint(board[x + 1][y + 2])));
			}
			else if (board[x + 1][y + 2] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y + 2));
			}
		}
		//-2,1
		if (x - 2 >= 0 && y + 1 < 8)
		{
			//적 말인 경우
			if (board[x - 2][y + 1] >= 'A' && board[x - 2][y + 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 2, y + 1, Chess::getPoint(board[x - 2][y + 1])));
			}
			else if (board[x - 2][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 2, y + 1));
			}
		}
		//-2,-1
		if (x - 2 >= 0 && y - 1 >= 0)
		{
			//적 말인 경우
			if (board[x - 2][y - 1] >= 'A' && board[x - 2][y - 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 2, y - 1, Chess::getPoint(board[x - 2][y - 1])));
			}
			else if (board[x - 2][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 2, y - 1));
			}
		}
		//-1,2
		if (x - 1 >= 0 && y + 2 < 8)
		{
			//적 말인 경우
			if (board[x - 1][y + 2] >= 'A' && board[x - 1][y + 2] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 1, y + 2, Chess::getPoint(board[x - 1][y + 2])));
			}
			else if (board[x - 1][y + 2] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 2));
			}
		}
		//-1,-2
		if (x - 1 >= 0 && y - 2 >= 0)
		{
			//적 말인 경우
			if (board[x - 1][y - 2] >= 'A' && board[x - 1][y - 2] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 1, y - 2, Chess::getPoint(board[x - 1][y - 2])));
			}
			else if (board[x - 1][y - 2] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y - 2));
			}
		}
	}
	else
	{
	//총 경우의 수 8가지
		//2,-1
		if (x + 2 < 8 && y - 1 >= 0)
		{
			//적 말인 경우
			if (board[x + 2][y - 1] >= 'a' && board[x + 2][y - 1] <= 'z')
			{
				tem.push_back(pMove(x, y, x + 2, y - 1, Chess::getPoint(board[x + 2][y - 1])));
			}
			else if (board[x + 2][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 2, y - 1));
			}
		}
		//2,1
		if (x + 2 < 8 && y + 1 < 8)
		{
			//적 말인 경우
			if (board[x + 2][y + 1] >= 'a' && board[x + 2][y + 1] <= 'z')
			{
				tem.push_back(pMove(x, y, x + 2, y + 1, Chess::getPoint(board[x + 2][y + 1])));
			}
			else if (board[x + 2][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 2, y + 1));
			}
		}
		//1, -2
		if (x + 1 < 8 && y - 2 >= 0)
		{
			//적 말인 경우
			if (board[x + 1][y - 2] >= 'a' && board[x + 1][y - 2] <= 'z')
			{
				tem.push_back(pMove(x, y, x + 1, y - 2, Chess::getPoint(board[x + 1][y - 2])));
			}
			else if (board[x + 1][y - 2] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y - 2));
			}
		}
		//1,2
		if (x + 1 < 8 && y + 2 < 8)
		{
			//적 말인 경우
			if (board[x + 1][y + 2] >= 'a' && board[x + 1][y + 2] <= 'z')
			{
				tem.push_back(pMove(x, y, x + 1, y + 2, Chess::getPoint(board[x + 1][y + 2])));
			}
			else if (board[x + 1][y + 2] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y + 2));
			}
		}
		//-2,1
		if (x - 2 >= 0 && y + 1 < 8)
		{
			//적 말인 경우
			if (board[x - 2][y + 1] >= 'a' && board[x - 2][y + 1] <= 'z')
			{
				tem.push_back(pMove(x, y, x - 2, y + 1, Chess::getPoint(board[x - 2][y + 1])));
			}
			else if (board[x - 2][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 2, y + 1));
			}
		}
		//-2,-1
		if (x - 2 >= 0 && y - 1 >= 0)
		{
			//적 말인 경우
			if (board[x - 2][y - 1] >= 'a' && board[x - 2][y - 1] <= 'z')
			{
				tem.push_back(pMove(x, y, x - 2, y - 1, Chess::getPoint(board[x - 2][y - 1])));
			}
			else if (board[x - 2][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 2, y - 1));
			}
		}
		//-1,2
		if (x - 1 >= 0 && y + 2 < 8)
		{
			//적 말인 경우
			if (board[x - 1][y + 2] >= 'a' && board[x - 1][y + 2] <= 'z')
			{
				tem.push_back(pMove(x, y, x - 1, y + 2, Chess::getPoint(board[x - 1][y + 2])));
			}
			else if (board[x - 1][y + 2] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 2));
			}
		}
		//-1,-2
		if (x - 1 >= 0 && y - 2 >= 0)
		{
			//적 말인 경우
			if (board[x - 1][y - 2] >= 'a' && board[x - 1][y - 2] <= 'z')
			{
				tem.push_back(pMove(x, y, x - 1, y - 2, Chess::getPoint(board[x - 1][y - 2])));
			}
			else if (board[x - 1][y - 2] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y - 2));
			}
		}
	}
	return tem;
}
vector<pMove> Chess::BishopMove(char** board, bool isComputer, int x, int y)
{
	vector<pMove> tem;
	int xindex;
	int yindex;
	if (isComputer)
	{
		//오른쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 7)
			{
				break;
			}
			xindex--;
			yindex++;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//오른쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 0)
			{
				break;
			}
			xindex++;
			yindex--;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 0)
			{
				break;
			}
			xindex--;
			yindex--;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 7)
			{
				break;
			}
			xindex++;
			yindex++;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
	}
	else
	{
		//오른쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 8)
			{
				break;
			}
			xindex--;
			yindex++;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//오른쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 8 || yindex == 0)
			{
				break;
			}
			xindex++;
			yindex--;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 0)
			{
				break;
			}
			xindex--;
			yindex--;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 8 || yindex == 8)
			{
				break;
			}
			xindex++;
			yindex++;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
	}
	return tem;
}
vector<pMove> Chess::KingMove(char** board, bool isComputer, int x, int y)
{
	vector<pMove> tem;
	if (isComputer)
	{
		//총 8가지 경우
		if (x + 1 < 8 && y + 1 < 8 )
		{
			if (board[x + 1][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y + 1));
			}
			else if (board[x + 1][y + 1] >= 'A' && board[x + 1][y + 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 1, y + 1, Chess::getPoint(board[x + 1][y + 1])));
			}
		}
		if (x + 1 < 8 && y - 1 >= 0)
		{
			if (board[x + 1][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y - 1));
			}
			else if (board[x + 1][y - 1] >= 'A' && board[x + 1][y - 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 1, y - 1, Chess::getPoint(board[x + 1][y - 1])));
			}
		}
		if (x + 1 < 8)
		{
			if (board[x + 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y));
			}
			else if (board[x + 1][y] >= 'A' && board[x + 1][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, x + 1, y, Chess::getPoint(board[x + 1][y])));
			}
		}
		if (x - 1 >= 8 && y + 1 < 8)
		{
			if (board[x - 1][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1));
			}
			else if (board[x - 1][y + 1] >= 'A' && board[x - 1][y + 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1, Chess::getPoint(board[x - 1][y + 1])));
			}
		}
		if (x - 1 >= 8 && y - 1 >= 0)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y - 1));
			}
			else if (board[x - 1][y - 1] >= 'A' && board[x - 1][y - 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 1, y - 1, Chess::getPoint(board[x - 1][y - 1])));
			}
		}
		if (x - 1 >= 8)
		{
			if (board[x - 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1));
			}
			else if (board[x - 1][y] >= 'A' && board[x - 1][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, x - 1, y, Chess::getPoint(board[x - 1][y])));
			}
		}
		if (y + 1 < 8)
		{
			if (board[x][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x, y + 1));
			}
			else if (board[x][y + 1] >= 'A' && board[x][y + 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x, y + 1, Chess::getPoint(board[x][y + 1])));
			}
		}
		if (y - 1 >= 0)
		{
			if (board[x][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x, y - 1));
			}
			else if (board[x][y - 1] >= 'A' && board[x][y - 1] <= 'Z')
			{
				tem.push_back(pMove(x, y, x, y - 1, Chess::getPoint(board[x][y - 1])));
			}
		}
	}
	else
	{
		if (x + 1 < 8 && y + 1 < 8)
		{
			if (board[x + 1][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y + 1));
			}
			else if (board[x + 1][y + 1] >= 'a' && board[x + 1][y + 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x + 1, y + 1, Chess::getPoint(board[x + 1][y + 1])));
			}
		}
		if (x + 1 < 8 && y - 1 > 0)
		{
			if (board[x + 1][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y - 1));
			}
			else if (board[x + 1][y - 1] >= 'a' && board[x + 1][y - 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x + 1, y - 1, Chess::getPoint(board[x + 1][y - 1])));
			}
		}
		if (x + 1 < 8)
		{
			if (board[x + 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y));
			}
			else if (board[x + 1][y] >= 'a' && board[x + 1][y] >= 'z')
			{
				tem.push_back(pMove(x, y, x + 1, y, Chess::getPoint(board[x + 1][y])));
			}
		}
		if (x - 1 >= 0 && y + 1 < 8)
		{
			if (board[x - 1][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1));
			}
			else if (board[x - 1][y + 1] >= 'a' && board[x - 1][y + 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1, Chess::getPoint(board[x - 1][y + 1])));
			}
		}
		if (x - 1 >= 0 && y - 1 >= 0)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y - 1));
			}
			else if (board[x - 1][y - 1] >= 'a' && board[x - 1][y - 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x - 1, y - 1, Chess::getPoint(board[x - 1][y - 1])));
			}
		}
		if (x - 1 >= 0)
		{
			if (board[x - 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y + 1));
			}
			else if (board[x - 1][y] >= 'a' && board[x - 1][y] >= 'z')
			{
				tem.push_back(pMove(x, y, x - 1, y, Chess::getPoint(board[x - 1][y])));
			}
		}
		if (y + 1 < 8)
		{
			if (board[x][y + 1] == ' ')
			{
				tem.push_back(pMove(x, y, x, y + 1));
			}
			else if (board[x][y + 1] >= 'a' && board[x][y + 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x, y + 1, Chess::getPoint(board[x][y + 1])));
			}
		}
		if (y - 1 >= 0)
		{
			if (board[x][y - 1] == ' ')
			{
				tem.push_back(pMove(x, y, x, y - 1));
			}
			else if (board[x][y - 1] >= 'a' && board[x][y - 1] >= 'z')
			{
				tem.push_back(pMove(x, y, x, y - 1, Chess::getPoint(board[x][y - 1])));
			}
		}
	}
	return tem;
}
vector<pMove> Chess::QueenMove(char** board, bool isComputer, int x, int y)
{
	int index;
	int xindex;
	int yindex;
	vector<pMove> tem;
	if (isComputer)
	{
		//위로
		index = x;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				break;
			}
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//아래
		index = x;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				break;
			}
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//오른쪽
		index = y;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				break;
			}
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				tem.push_back(pMove(x, y, x, index, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//왼쪽
		index = y;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				break;
			}
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//오른쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 7)
			{
				break;
			}
			xindex--;
			yindex++;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//오른쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 0)
			{
				break;
			}
			xindex++;
			yindex--;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 0)
			{
				break;
			}
			xindex--;
			yindex--;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 7)
			{
				break;
			}
			xindex++;
			yindex++;
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
	}
	else
	{
		//위로
		index = x;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				break;
			}
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//아래
		index = x;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[index][y] >= 'A' || board[index][y] <= 'Z')
			{
				break;
			}
			if (board[index][y] >= 'a' || board[index][y] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, index, y));
		}
		//오른쪽
		index = y;
		while (true)
		{
			if (index == 7)
			{
				break;
			}
			index++;
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				break;
			}
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				tem.push_back(pMove(x, y, x, index, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//왼쪽
		index = y;
		while (true)
		{
			if (index == 0)
			{
				break;
			}
			index--;
			if (board[x][index] >= 'A' || board[x][index] <= 'Z')
			{
				break;
			}
			if (board[x][index] >= 'a' || board[x][index] <= 'z')
			{
				tem.push_back(pMove(x, y, index, y, Chess::getPoint(board[index][y])));
				break;
			}
			tem.push_back(pMove(x, y, x, index));
		}
		//오른쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 7)
			{
				break;
			}
			xindex--;
			yindex++;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//오른쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 0)
			{
				break;
			}
			xindex++;
			yindex--;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 위
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 0 || yindex == 0)
			{
				break;
			}
			xindex--;
			yindex--;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
		//왼쪽 대각선 아래
		xindex = x;
		yindex = y;
		while (true)
		{
			if (xindex == 7 || yindex == 7)
			{
				break;
			}
			xindex++;
			yindex++;
			if (board[xindex][yindex] >= 'A' || board[xindex][yindex] <= 'Z')
			{
				break;
			}
			if (board[xindex][yindex] >= 'a' || board[xindex][yindex] <= 'z')
			{
				tem.push_back(pMove(x, y, xindex, yindex, Chess::getPoint(board[xindex][yindex])));
				break;
			}
			tem.push_back(pMove(x, y, xindex, yindex));
		}
	}
	return tem;
}
vector<pMove> Chess::PawnsMove(char** board, bool isComputer, int x, int y)
{
	vector<pMove> tem;
	if (isComputer)
	{
		if(x == 6)
		{
			//6번쨰 줄에 있으면 1칸 or 2칸 이동 가능
			//만약 적 말이 자신의 칸 앞에 있으면 전진 불가능
			if (board[x - 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y));
			}
			if (board[x - 2][y] == ' ')
			{
				tem.push_back(pMove(x, y, x - 2, y));
			}
			//만약 상대 말이 오른쪽 왼쪽 대각선위에 있으면 잡아먹으면서 해당 칸으로 이동 가능
			if (y - 1 >= 0)
			{
				if (board[x - 1][y - 1] >= 'A' && board[x - 1][y - 1] <= 'Z')
				{
					tem.push_back(pMove(x, y, x + 1, y - 1, Chess::getPoint(board[x + 1][y - 1])));
				}
			}
			if (y + 1 <= 7)
			{
				if (board[x - 1][y + 1] >= 'A' && board[x - 1][y + 1] <= 'Z')
				{
					tem.push_back(pMove(x, y, x - 1, y + 1, Chess::getPoint(board[x - 1][y - 1])));
				}
			}
		}
		else if (x - 1 >= 0)
		{
			//외에는 1칸 전진만 
			//만약 적 말이 자신의 칸 앞에 있으면 전진 불가능
			if (board[x - 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x - 1, y));
			}
			//만약 상대 말이 오른쪽 왼쪽 대각선위에 있으면 잡아먹으면서 해당 칸으로 이동 가능
			if (y - 1 >= 0)
			{
				if (board[x - 1][y - 1] >= 'A' && board[x - 1][y - 1] <= 'Z')
				{
					tem.push_back(pMove(x, y, x - 1, y - 1, Chess::getPoint(board[x - 1][y - 1])));
				}
			}
			if (y + 1 <= 7)
			{
				if (board[x - 1][y + 1] >= 'A' && board[x - 1][y + 1] <= 'Z')
				{
					tem.push_back(pMove(x, y, x - 1, y + 1, Chess::getPoint(board[x - 1][y - 1])));
				}
			}
		}
	}
	else
	{
		if (x == 1)
		{
			//6번쨰 줄에 있으면 1칸 or 2칸 이동 가능
			//만약 적 말이 자신의 칸 앞에 있으면 전진 불가능
			if (board[x + 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y));
			}
			if (board[x + 2][y] == ' ')
			{
				tem.push_back(pMove(x, y, x + 2, y));
			}
			//만약 상대 말이 오른쪽 왼쪽 대각선위에 있으면 잡아먹으면서 해당 칸으로 이동 가능
			if (y - 1 >= 0)
			{
				if (board[x + 1][y - 1] >= 'a' && board[x + 1][y - 1] <= 'z')
				{
					tem.push_back(pMove(x, y, x + 1, y - 1, Chess::getPoint(board[x + 1][y - 1])));
				}
			}
			if (y + 1 <= 7)
			{
				if (board[x + 1][y + 1] >= 'a' && board[x + 1][y + 1] <= 'z')
				{
					tem.push_back(pMove(x, y, x + 1, y + 1, Chess::getPoint(board[x + 1][y - 1])));
				}
			}
		}
		else if (x + 1 < 8)
		{
			//외에는 1칸 전진만 
			//만약 적 말이 자신의 칸 앞에 있으면 전진 불가능
			if (board[x + 1][y] == ' ')
			{
				tem.push_back(pMove(x, y, x + 1, y));
			}
			//만약 상대 말이 오른쪽 왼쪽 대각선위에 있으면 잡아먹으면서 해당 칸으로 이동 가능
			if (y - 1 >= 0)
			{
				if (board[x + 1][y - 1] >= 'a' && board[x + 1][y - 1] <= 'z')
				{
					tem.push_back(pMove(x, y, x + 1, y - 1, Chess::getPoint(board[x + 1][y - 1])));
				}
			}
			if (y + 1 <= 7)
			{
				if (board[x + 1][y + 1] >= 'a' && board[x + 1][y + 1] <= 'z')
				{
					tem.push_back(pMove(x, y, x + 1, y + 1, Chess::getPoint(board[x + 1][y - 1])));
				}
			}
		}
	}
	return tem;
}