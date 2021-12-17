#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

bool gameOver;
bool Player_one_active;
bool Ball_hit;
bool Winner_player_one;

const int width = 112;
const int height = 21;

int player_one_position_x, player_one_position_y;
int player_two_position_x, player_two_position_y;
int ball_position_x, ball_position_y;
int score;
int random_direction;

string mode;
string repeat;

enum eDirection { STOP = 0, PLAYER_ONE_DOWN, PLAYER_ONE_UP, PLAYER_TWO_DOWN, PLAYER_TWO_UP, PAUSE};
eDirection dir;

void Setup()
{
	gameOver = false;
	Player_one_active = false;

	dir = STOP;

	player_one_position_x = width - (width - 1);
	player_one_position_y = height / 2;

	player_two_position_x = width - 3;
	player_two_position_y = height / 2;

	ball_position_x = width - (width - 2);
	ball_position_y = height / 2 - 1;

	score = -1;

	srand(time(NULL));
	random_direction = rand() % 2;

	cout << "Chose game mode PvP/PvE (Enter pvp or pve): ";
	cin >> mode;

	if (mode != "pvp" && mode != "pve")
	{
		while (true)
		{
			cout << "Please, enter correct answer (pvp or pve)";
			cin >> mode;
			if (mode == "pvp" || mode == "pve")
			{
				break;
			}
		}
	}

	if (random_direction == 0)
	{
		Ball_hit = false;
	}
	else
	{
		Ball_hit = true;
	}
}

void Draw()
{
	system("cls");

	for (int index = 0; index < width + 1; index++)
	{
		cout << "#";
	}
	cout << endl;

	for (int index = 0; index < height; index++)
	{
		for (int second_index = 0; second_index < width; second_index++)
		{
			if (second_index == 0 || second_index == width - 1)
			{
				cout << "#";
			}

			if ((index == player_one_position_y || index == player_one_position_y - 1 || index == player_one_position_y + 1 || index == player_one_position_y - 2 || index == player_one_position_y + 2) && second_index == player_one_position_x)
			{
				cout << "|";
			}
			else if ((index == player_two_position_y || index == player_two_position_y - 1 || index == player_two_position_y + 1 || index == player_two_position_y - 2 || index == player_two_position_y + 2) && second_index == player_two_position_x)
			{
				cout << "|";
			}
			else if (index == ball_position_y && second_index == ball_position_x)
			{
				cout << "o";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	for (int index = 0; index < width + 1; index++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 72:
			dir = PLAYER_ONE_UP;
			break;
		case 80:
			dir = PLAYER_ONE_DOWN;
			break;
		case 73:
			dir = PLAYER_TWO_UP;
			break;
		case 81:
			dir = PLAYER_TWO_DOWN;
			break;
		case 8:
			dir = PAUSE;
		default:
			break;
		}
	}
}

void Player_one()
{
	if (player_one_position_y != height - 3 && dir == PLAYER_ONE_DOWN)
	{
		player_one_position_y += 2;
		dir = STOP;
	}
	else if (player_one_position_y != height - (height - 2) && dir == PLAYER_ONE_UP)
	{
		dir = STOP;
		player_one_position_y -= 2;
	}
}

void Player_two()
{
	if (player_two_position_y != height - 3 && dir == PLAYER_TWO_DOWN)
	{
		dir = STOP;
		player_two_position_y += 2;
	}
	else if (player_two_position_y != height - (height - 2) && dir == PLAYER_TWO_UP)
	{
		dir = STOP;
		player_two_position_y -= 2;
	}
}

void Bot()
{
	if (ball_position_x > width - 3 - 18)
	{
		if (ball_position_y > player_two_position_y + 2)
		{
			player_two_position_y += 2;
		}
		else if (ball_position_y < player_two_position_y - 2)
		{
			player_two_position_y -= 2;
		}
	}
}

void Logic()
{
	if (mode == "pvp")
	{
		Player_one();
		Player_two();
		
	}
	else if (mode == "pve")
	{
		Player_one();
		Bot();
	}
	if (ball_position_x == player_one_position_x + 1 && (ball_position_y == player_one_position_y || ball_position_y == player_one_position_y - 1 || ball_position_y == player_one_position_y + 1 || ball_position_y == player_one_position_y - 2 || ball_position_y == player_one_position_y + 2))
	{
		Player_one_active = false;
		score++;
	}
	else if (ball_position_x == player_one_position_x - 1 && (ball_position_y != player_one_position_y || ball_position_y != player_one_position_y - 1 || ball_position_y != player_one_position_y + 1 || ball_position_y != player_one_position_y - 2 || ball_position_y != player_one_position_y + 2))
	{
		gameOver = true;
		Winner_player_one = false;
	}

	if (ball_position_x == player_two_position_x - 1 && (ball_position_y == player_two_position_y || ball_position_y == player_two_position_y - 1 || ball_position_y == player_two_position_y + 1 || ball_position_y == player_two_position_y - 2 || ball_position_y == player_two_position_y + 2))
	{
		Player_one_active = true;
		if (mode == "pvp")
		{
			score++;
		}
	}
	else if (ball_position_x == player_two_position_x + 1 && (ball_position_y != player_two_position_y || ball_position_y != player_two_position_y - 1 || ball_position_y != player_two_position_y + 1 || ball_position_y == player_two_position_y - 2 || ball_position_y != player_two_position_y + 2))
	{
		gameOver = true;
		Winner_player_one = true;
	}
	

	if (ball_position_y == height - 1)
	{
		Ball_hit = false;
	}
	else if (ball_position_y == 0)
	{
		Ball_hit = true;
	}

	if (!Player_one_active)
	{
		
		ball_position_x += 2;

	}
	else if (Player_one_active)
	{
		ball_position_x -= 2;
	}

	if (Ball_hit)
	{
		ball_position_y++;
		
	}
	else if (!Ball_hit)
	{
		ball_position_y--;
	}
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 945, 450, TRUE);

	repeat = "yes";

	cout << "WARNING!!!\n" << endl;
	cout << "Control is carried out using the up/down arrows for the left player\nand using the PU and PD keys for the right player\n" << endl;

	while (repeat == "yes")
	{
		Setup();

		while (!gameOver)
		{
			if (dir == PAUSE)
			{
				system("pause");
				dir = STOP;
			}
			Draw();
			Input();
			Logic();
		}

		system("cls");

		if (mode == "pvp")
		{
			if (Winner_player_one)
			{
				cout << "Player one is winner!!!" << endl;
			}
			else if (!Winner_player_one)
			{
				cout << "Player two is winner!!!" << endl;
			}
			cout << "Score: " << score << endl;
		}
		else if (mode == "pve")
		{
			cout << "Game over" << endl;
			cout << "Your score: " << score << endl;
		}
		
		cout << "Repeat? (Enter yes or no): ";
		cin >> repeat;
		if (repeat != "yes" && repeat != "no")
		{
			while (true)
			{
				cout << "Please, enter correct answer (Enter yes or no)";
				cin >> repeat;
				if (repeat == "yes" || repeat == "no")
				{
					break;
				}
			}
		}
	}
	
	return 0;
}
