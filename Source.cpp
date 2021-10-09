#include <iostream>
#include <cstdlib>

using namespace std;

//Define the rows/columns for the martix
#define ROW 6
#define COLUMN 7

//Function called before main.
void DisplayMatrix();
void PlayerPlacement(int player);
bool DiagnolWinLeftRight(int x, int y, int player);
bool DiagnolWinRightLeft(int x, int y, int player);
bool VerticalWin(int x, int y, int player);
bool HorizontalWin(int x, int y, int player);
bool HasWon(int x, int y, int player);

int moveX, moveY;

//martix displayed using blanks if = 0.
int matrix[ROW][COLUMN] = { { 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 } };

int main()
{
	//setting them to defualt to eliminate errors
	int counter = 0;
	bool isWinner = false;

	DisplayMatrix();

	//swapping between players turns ever turn for 21 turns.
	for (int i = 0; i < 21; i++)
	{
		PlayerPlacement(1);
		DisplayMatrix();
		isWinner = HasWon(moveX, moveY, 1);
		if (isWinner)
		{
			cout << "Player 1 has won the game!" << endl;
			break;
		}
		PlayerPlacement(2);
		DisplayMatrix();
		isWinner = HasWon(moveX, moveY, 2);
		if (isWinner)
		{
			cout << "Player 2 has won the game!" << endl;
			break;
		}
	}
	//End of program after 21 loops or player won.

	return 0;
}

//Display the martix/Matrix
void DisplayMatrix()
{
	cout << "Please select a number from 1-7" << endl;
	cout << "+---------------------+" << endl;;
	cout << "| 1| 2| 3| 4| 5| 6| 7 |" << endl;
	cout << "+---------------------+" << endl;

	//When 0 leave blank, if player 1 then = X and player 2 = O
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			cout << "| ";
			if (matrix[i][j] == 0) cout << " ";
			else if (matrix[i][j] == 1) cout << "X";
			else if (matrix[i][j] == 2) cout << "O";
		}
		cout << "\n+--------------------+" << endl;
	}
}

//take in user input and drop to bottom.
void PlayerPlacement(int player)
{

	int playerChoice;
	cout << "\nPlayer " << player << " your up! Please select a number (1-7): ";
	cin >> playerChoice;

	while (playerChoice > COLUMN || playerChoice <= 0)
	{
		cout << "\nPlease select a number again (1-7): ";
		cin >> playerChoice;
	}

	int num = 0;
	while (matrix[(ROW - 1) - num][(playerChoice - 1)] != 0)
	{
		num++;
		if (num > (ROW - 1))
		{
			cout << "\nPlease select a number again (1-7): ";
			cin >> playerChoice;
			num = 0;
		}
	};

	matrix[(ROW - 1) - num][playerChoice - 1] = player;
	moveY = (ROW - 1) - num;
	moveX = playerChoice - 1;
}

//Left to right diagnol win
bool DiagnolWinLeftRight(int x, int y, int player)
{
	int count = 1;
	int score = 1;

	while ((y - count >= 0) && (x + count < COLUMN))
	{
		//Check left to right
		if (matrix[y - count][x + count] == player)
		{
			count++;
			score++;
		}
		//If no connect 4 then leave loop
		else 
			break;
	}

	count = 1;
	while ((y + count < ROW) && (x - count >= 0))
	{
		//Check right to left
		if (matrix[y + count][x - count] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else 
			break;
	}
	if (score == 4)
		return true;
	else 
		return false;
}

//Right to Left diagnol win
bool DiagnolWinRightLeft(int x, int y, int player)
{
	int count = 1;
	int score = 1;

	while ((y + count >= 0) && (x + count < COLUMN))
	{
		//check right to left
		if (matrix[y + count][x + count] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else 
			break;
	}

	count = 1;
	while ((y - count < ROW) && (x - count >= 0))
	{
		//Check left to right
		if (matrix[y - count][x - count] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else
			break;
	}
	if (score == 4) 
		return true;
	else 
		return false;
}

//Vert win
bool VerticalWin(int x, int y, int player)
{
	int count = 1;
	int score = 1;

	while (y + count >= 0 && y + count < ROW)
	{
		if (matrix[y + count][x] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else 
			break;
	}
	if (score == 4) 
		return true;
	else 
		return false;
}

//Hor win
bool HorizontalWin(int x, int y, int player)
{
	int score = 1;
	int count = 1;

	while ((x + count >= 0) && (x + count < COLUMN))
	{
		//Check to see if four in a row going left
		if (matrix[y][x + count] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else 
			break;
	}

	count = 1;
	while ((x - count < COLUMN) && (x - count >= 0))
	{
		//Check to see if four in a row going right
		if (matrix[y][x - count] == player)
		{
			count++;
			score++;
		}
		//Same leave loop if no connect 4
		else 
			break;
	}
	if (score == 4) 
		return true;
	else 
		return false;
}

//If four connects then = win
bool HasWon(int x, int y, int player)
{
	bool winner;

	if (DiagnolWinLeftRight(x, y, player))
		return true;
	if (DiagnolWinRightLeft(x, y, player))
		return true;
	if (VerticalWin(x, y, player))
		return true;
	if (HorizontalWin(x, y, player))
		return true;
	else
		return false;
}