#include <iostream>
#include <fstream>
//#include <time.h>
#include <iomanip>
#include <cstdlib>
#include <string>
//#include <Windows.h>
using namespace std;
void menu();
void subMenu();
void instructions();
void credits();
bool validity(int kase, int y, int x);
void gameplay(int size, int kase);
void display(char board[][20], int size);
void place(char board[][20], int size);
bool sunk(char board[][20], char check, int size);
void write(char board[][20], ofstream& write, int size, int kase);
void readf(char board[][20], ifstream& read, int size, int kase);
int main()
{
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(handle, 0 | FOREGROUND_INTENSITY);
	//sf::Music music;

	//if (!music.openFromFile("background.ogg"))
	//{
	//	cout << "Error opening the music file!" << endl;
	//}
	//music.play();


	srand(time(0));
	int option = 0, sub_option, size;

	char easy[20][20], medium[20][20], hard[20][20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			easy[i][j] = 'o';
			medium[i][j] = 'o';
			hard[i][j] = 'o';
		}
	}
	ofstream easyW("Easy Board.txt");
	ofstream mediumW("Medium Board.txt");
	ofstream hardW("Hard Board.txt");


	place(easy, 10);
	place(medium, 15);
	place(hard, 20);
	write(easy, easyW, 10, 1);
	write(medium, mediumW, 15, 2);
	write(hard, hardW, 20, 3);


	while (option != 4)
	{
		menu();
		cin >> option;
		switch (option)
		{
		case 1:
			subMenu();
			cin >> sub_option;
			system("cls");
			switch (sub_option)
			{
			case 1:
				size = 10;
				gameplay(size, 1);
				break;
			case 2:
				size = 15;
				gameplay(size, 2);
				break;
			case 3:
				size = 20;
				gameplay(size, 3);
				break;
			default:
				cout << "Enter a valid input!" << endl;
			}
			break;
		case 2:
			system("cls");
			instructions();
			break;
		case 3:
			system("cls");
			credits();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "Enter a valid option!" << endl;
		}
		system("pause > 0");
		system("cls");
	}
}
void gameplay(int size, int kase)
{
	//sf::SoundBuffer miss;
	//sf::SoundBuffer hit;
	//sf::SoundBuffer explosion;

	//if (!miss.loadFromFile("miss.ogg"))
	//{
	//	cout << "Error opening miss effect!" << endl;
	//}
	//if (!hit.loadFromFile("hit.ogg"))
	//{
	//	cout << "Error opening hit effect!" << endl;
	//}
	//if (!explosion.loadFromFile("explosion.ogg"))
	//{
	//	cout << "Error opening exlposion effect!" << endl;
	//}
	//sf::Sound missS, hitS, explosionS;
	//missS.setBuffer(miss);
	//hitS.setBuffer(hit);
	//explosionS.setBuffer(explosion);

	//sf::Clock timer;
	//int clock;
	float score = 0;
	char comp[20][20], user[20][20], firingBoard[20][20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			comp[i][j] = 'o';
			firingBoard[i][j] = 'o';
			user[i][j] = 'o';
		}
	}
	int hit1, hit2;
	string fire;
	ofstream userBoard("Game Board File - User.txt");
	ifstream read;

	if (kase == 1)
		read.open("Easy Board.txt");
	if (kase == 2)
		read.open("Medium Board.txt");
	if (kase == 3)
		read.open("Hard Board.txt");

	// Declaring booleans
	bool sunkA_u = true, sunkB_u = true, sunkC_u = true, sunkD_u = true, sunkS_u = true;
	bool all_sunk = false;
	bool sunkA_c = true, sunkB_c = true, sunkC_c = true, sunkD_c = true, sunkS_c = true;
	bool first1 = true, first2 = true, first3 = true, first4 = true, first5 = true;

	// Placing ships in the user's board
	place(user, size);

	// Writing the board to a file.
	write(user, userBoard, size, kase);
	userBoard.close();

	while (!all_sunk)
	{
		// Gets the time elapsed since the program has been running
		/*sf::Time time = timer.getElapsedTime();
		clock = time.asSeconds();
		cout << "\n\n\tTime Elapsed:\t\tYour Score is: " << score << endl << endl;
		cout << "\t\tSeconds: " << clock << endl;
		cout << "\t\tMinutes: " << clock / 60 << endl << endl << endl;*/

		// Reading the computers board
		readf(comp, read, size, kase);

		// Styling
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		cout << "\t\t O P P O N E N T S   B O A R D " << endl << endl;
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		// ...and displaying the board
		display(firingBoard, size);

		// Styling
		cout << "\n\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		cout << "\t\t   Y O U R   B O A R D " << endl << endl;
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		// ...and displaying the board
		display(user, size);

		cout << "\n\t    Press any key to start firing!";
		system("pause > 0");

		system("cls");
		/*time = timer.getElapsedTime();
		clock = time.asSeconds();
		cout << "\n\n\tTime Elapsed:\t\tYour Score is: " << score << endl << endl;
		cout << "\t\tSeconds: " << clock << endl;
		cout << "\t\tMinutes: " << clock / 60 << endl << endl << endl;*/
		cout << "\t    Select a panel to fire at!\n" << endl;


		int x, y;
		bool valid = false;

		// Loop runs until the user has enters a valid input
		while (!valid)
		{
			cout << "\n\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
			cout << "\t\t   F I R I N G   B O A R D " << endl << endl;
			cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
			display(firingBoard, size);
			// Taking input
			cout << "\n\n\t   Format is 'A5'" << endl;
			cout << "\n\t   Where do you want to fire?\t";
			cin >> fire;

			// Checking if the user has input a valid position
			y = fire[0] - 65;
			if (fire.size() <= 2)
				x = int(fire[1]) - 48;
			else
				x = (int(fire[1]) - 48) * 10 + (int(fire[2]) - 48);

			valid = validity(kase, y, x);
			system("cls");
			if (!valid)
				cout << "Enter valid input!" << endl;
		}

		// The user is firing
		if (comp[y][x] != 'o' && comp[y][x] != 'M')
		{
			firingBoard[y][x] = 'H';
			comp[y][x] = 'H';
			score += 1;
			//hitS.play();
		}
		else
		{
			firingBoard[y][x] = 'M';
			comp[y][x] = 'M';
			score -= 0.25;
			//missS.play();
		}

		system("cls");

		// Styling
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		cout << "\t\t O P P O N E N T S   B O A R D " << endl << endl;
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		// ...and displaying the board
		display(firingBoard, size);

		// Styling
		cout << "\n\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		cout << "\t\t   Y O U R   B O A R D " << endl << endl;
		cout << "\t" << setw(20 + (kase * 23)) << setfill('*') << "*" << endl << endl;
		// ...and displaying the board
		display(user, size);

		hit1 = rand() % 10;
		hit2 = rand() % 10;
		// The computer is firing!
		if (user[hit1][hit2] != 'o' && user[y][x] != 'M')
		{
			user[hit1][hit2] = 'H';
		}
		else
		{
			user[hit1][hit2] = 'M';
		}

		// Picking a new location to fire at!
		hit1 = rand() % 10;
		hit2 = rand() % 10;

		system("cls");
		sunkA_c = false;
		sunkB_c = false;
		sunkC_c = false;
		sunkD_c = false;
		sunkS_c = false;

		// Checking individually if a ship has sunk - Computer
		sunkA_c = sunk(comp, 'A', size);
		if (!sunkA_c && first1)
		{
			cout << "\n\n\tYou sunk the opponents Aircraft Carrier!" << endl;
			cout << "\n\n\t10 points!" << endl;
			score += 10;
			first1 = false;
			//explosionS.play();
		}
		sunkB_c = sunk(comp, 'B', size);
		if (!sunkB_c && first2)
		{
			cout << "\n\n\tYou sunk the opponents Battleship!" << endl;
			cout << "\n\n\t8 points!" << endl;
			score += 8;
			first2 = false;
			//explosionS.play();
		}
		sunkC_c = sunk(comp, 'C', size);
		if (!sunkC_c && first3)
		{
			cout << "\n\n\tYou sunk the opponents Cruiser!" << endl;
			cout << "\n\n\t6 points!" << endl;
			score += 6;
			first3 = false;
			//explosionS.play();
		}
		sunkD_c = sunk(comp, 'D', size);
		if (!sunkD_c && first4)
		{
			cout << "\n\n\tYou sunk the opponents Destroyer!" << endl;
			cout << "\n\n\t4 points!" << endl;
			score += 4;
			first4 = false;
			//explosionS.play();
		}
		sunkS_c = sunk(comp, 'S', size);
		if (!sunkS_c && first5)
		{
			cout << "\n\n\tYou sunk the opponents Submarine!" << endl;
			cout << "\n\n\t6 points!" << endl;
			score += 6;
			first5 = false;
			//explosionS.play();
		}

		sunkA_u = false;
		sunkB_u = false;
		sunkC_u = false;
		sunkD_u = false;
		sunkS_u = false;


		// Checking individually if a ship has sunk - User
		sunkA_u = sunk(user, 'A', size);
		if (!sunkA_u)
		{
			cout << "Opponent sunk your Submarine!" << endl;
			//explosionS.play();
		}
		sunkB_u = sunk(user, 'B', size);
		if (!sunkB_u)
		{
			cout << "Opponent sunk your Submarine!" << endl;
			//explosionS.play();
		}
		sunkC_u = sunk(user, 'C', size);
		if (!sunkC_u)
		{
			cout << "Opponent sunk your Submarine!" << endl;
			//explosionS.play();
		}
		sunkD_u = sunk(user, 'D', size);
		if (!sunkD_u)
		{
			cout << "Opponent sunk your Submarine!" << endl;
			//explosionS.play();
		}
		sunkS_u = sunk(user, 'S', size);
		if (!sunkS_u)
		{
			cout << "Opponent sunk your Submarine!" << endl;
			//explosionS.play();
		}

		// If all ships belonging to the computer are sunk, then the user has won the game.
		if (!sunkA_c && !sunkB_c && !sunkC_c && !sunkD_c && !sunkS_c)
		{
			cout << "Congratulations! You won the game!" << endl;
			all_sunk = true;
		}

		// ...and vice versa
		if (!sunkA_u && !sunkB_u && !sunkC_u && !sunkD_u && !sunkS_u)
		{
			cout << "Oh, snap! You lost the game! Better luck next time!" << endl;
			all_sunk = true;
		}
	}
}
void place(char board[][20], int size)
{
	// ************* AIRCRAFT CARRIER *************

	// Placing the Aircraft Carrier
	int AC = rand() % (size - 5),
		position = rand() % size,
		randomizer = rand() % 2;	// Randomizing the randomizer
	for (int i = 0; i < 5 && randomizer == 1; i++)
	{
		board[position][AC] = 'A';
		AC++;
	}
	for (int i = 0; i < 5 && randomizer == 0; i++)
	{
		board[AC][position] = 'A';
		AC++;
	}

	// ************* BATTLESHIP *************

	int battleship = rand() % (size - 6);
	position = rand() % size;		// Creating another random number for position 2
	randomizer = rand() % 2;


	// Checking if the Battleship will overlap the existing ships, and fixing it.
	bool overlap = true;
	while (overlap)
	{
		overlap = false;
		for (int i = 0; i < 4; i++)
		{
			if (board[position][battleship + i] == 'A' || board[battleship + i][position] == 'A')
			{
				overlap = true;
				break;
			}
		}
		if (overlap == true)
		{
			battleship = rand() % (size - 6);
			position = rand() % size;
		}
	}

	// Placing the Battleship

	for (int i = 0; i < 4 && randomizer == 0; i++)
	{
		board[position][battleship + i] = 'B';
	}
	for (int i = 0; i < 4 && randomizer == 1; i++)
	{
		board[battleship + i][position] = 'B';
	}

	// ************* CRUISER *************

	int cruiser = rand() % (size - 7);
	position = rand() % size;		// Creating another random number for position 2
	randomizer = rand() % 2;


	// Checking if the Cruiser will overlap the existing ships, and fixing it.
	overlap = true;
	while (overlap)
	{
		overlap = false;
		for (int i = 0; i < 3; i++)
		{
			if (board[position][cruiser + i] == 'A' || board[cruiser + i][position] == 'A'
				|| board[position][cruiser + i] == 'B' || board[cruiser + i][position] == 'B')
			{
				overlap = true;
				break;
			}
		}
		if (overlap == true)
		{
			cruiser = rand() % (size - 7);
			position = rand() % size;
		}
	}

	// Placing the Cruiser

	for (int i = 0; i < 3 && randomizer == 0; i++)
	{
		board[position][cruiser + i] = 'C';
	}
	for (int i = 0; i < 3 && randomizer == 1; i++)
	{
		board[cruiser + i][position] = 'C';
	}

	// ************* SUBMARINE *************

	int submarine = rand() % (size - 7);
	position = rand() % size;		// Creating another random number for position 2
	randomizer = rand() % 2;


	// Checking if the Submarine will overlap the existing ships, and fixing it.
	overlap = true;
	while (overlap)
	{
		overlap = false;
		for (int i = 0; i < 3; i++)
		{
			if (board[position][submarine + i] == 'A' || board[submarine + i][position] == 'A' || board[position][submarine + i] == 'B'
				|| board[submarine + i][position] == 'B' || board[position][submarine + i] == 'C' || board[submarine + i][position] == 'C')
			{
				overlap = true;
				break;
			}
		}
		if (overlap == true)
		{
			submarine = rand() % (size - 7);
			position = rand() % size;
		}
	}

	//// Placing the Submarine

	for (int i = 0; i < 3 && randomizer == 0; i++)
	{
		board[position][submarine + i] = 'S';
	}
	for (int i = 0; i < 3 && randomizer == 1; i++)
	{
		board[submarine + i][position] = 'S';
	}

	// ************* DESTROYER *************

	int destroyer = rand() % (size - 8);
	position = rand() % size;		// Creating another random number for position 2
	randomizer = rand() % 2;


	// Checking if the Destroyer will overlap the existing ships, and fixing it.
	overlap = true;
	while (overlap)
	{
		overlap = false;
		for (int i = 0; i < 2; i++)
		{
			if (board[position][destroyer + i] == 'A' || board[destroyer + i][position] == 'A' || board[position][destroyer + i] == 'B'
				|| board[destroyer + i][position] == 'B' || board[position][destroyer + i] == 'C' || board[destroyer + i][position] == 'C'
				|| board[position][destroyer + i] == 'S' || board[destroyer + i][position] == 'S')
			{
				overlap = true;
				break;
			}
		}
		if (overlap == true)
		{
			destroyer = rand() % (size - 8);
			position = rand() % size;
		}
	}

	// Placing the Destroyer

	for (int i = 0; i < 2 && randomizer == 0; i++)
	{
		board[position][destroyer + i] = 'D';
	}
	for (int i = 0; i < 2 && randomizer == 1; i++)
	{
		board[destroyer + i][position] = 'D';
	}

}
void display(char board[][20], int size)
{
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(handle, 0 | FOREGROUND_INTENSITY);
	cout << "\n\t  ";

	// This chunk prints the column number on the top.
	for (int i = 0; i < size; i++)
	{
		cout << "   " << i;
	}
	cout << endl << endl;
	for (int i = 0; i < size; i++)
	{
		// 65 is the ASCII for 'A'. This chunk prints the Alphabets.
		cout << "\t" << char(65 + i) << "    ";
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == 'M')
			{
				//SetConsoleTextAttribute(handle, 4 | FOREGROUND_INTENSITY);
				cout << board[i][j] << "   ";
				continue;
			}
			if (board[i][j] == 'H')
			{
				//SetConsoleTextAttribute(handle, 2 | FOREGROUND_INTENSITY);
				cout << board[i][j] << "   ";
			}
			else
			{
				//SetConsoleTextAttribute(handle, 0 | FOREGROUND_INTENSITY);
				cout << board[i][j] << "   ";
			}

			if (j >= 10)
				cout << " ";
		}
		cout << endl;
	}
}
bool validity(int kase, int y, int x)
{
	if (y < 0 || y >(4 + (kase * 5)) || x < 0 || x >(4 + (kase * 5)))
	{
		cout << "Enter a valid input!" << endl;
		return false;
	}
	else
		return true;
}
bool sunk(char board[][20], char check, int size)
{
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == check)
			{
				found = true;
			}
		}
	}
	return found;
}
void write(char board[][20], ofstream& write, int size, int kase)
{
	write << "Difficulty level : ";
	if (kase == 1)
		write << "Easy\n" << endl;
	if (kase == 2)
		write << "Medium\n" << endl;
	if (kase == 3)
		write << "Hard\n" << endl;
	for (int i = 0; i < size; i++)
	{
		write << "    ";
		for (int j = 0; j < size; j++)
		{
			write << board[i][j] << "   ";
			if (j >= 10)
				write << " ";
		}
		write << endl;
	}
}
void readf(char board[][20], ifstream& read, int size, int kase)
{
	read.ignore(100, '\n');

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			read >> board[i][j];
		}
	}
}
void menu()
{
	cout << "\n\n\n\n";
	cout << "\t\t" << setw(33) << setfill('*') << " Welcome to " << setw(20) << "*" << endl;
	cout << "\n\t\t\t\t  B A T T L E S H I P" << endl;
	cout << "\n\t\t" << setw(53) << "*" << endl;
	cout << "\n\t\t\t    W H A T  D O  Y O U  D E S I R E ?\n\n" << endl;
	cout << "\n\t\t1 - Play Game\n"
		<< "\n\t\t2 - Instructions\n"
		<< "\n\t\t3 - Credits\n"
		<< "\n\t\t4 - Exit\n"
		<< "\n\t\tChoice: ";
}
void subMenu()
{
	system("cls");
	cout << "\n\n\n\n";
	cout << "\t\t" << setw(53) << "*" << endl;
	cout << "\n\t\t    S E L E C T   D I F F I C U L T Y   L E V E L" << endl << endl;
	cout << "\t\t" << setw(53) << "*" << endl;
	cout << "\n\t\t1 - Easy\n"
		<< "\n\t\t2 - Medium\n"
		<< "\n\t\t3 - Hard\n"
		<< "\n\t\tChoice: ";
}
void instructions()
{
	cout << "\n\tIn this game you will play against the computer." << endl
		<< "\n\tYou have 5 ships of differing size(2 to 5) squares."
		<< "\n\tYour ships will be placed on the board randomly."
		<< "\n\tThe player will pick a square at random"
		<< "\n\tcalling it by its reference of column reference, row number(C3 for example)." << endl
		<< "\n\tThis represents their firing a missile directly at that square. If the opposing player has any part"
		<< "\n\tof one of their ships positioned on this square the square will be marked 'H' on their board"
		<< "\n\twhich part has been hit. Equally the attacking player will have their board marked with an 'H' as well"
		<< "\n\ton their firing board to show a hit.The computer will then make a random shot at your board." << endl
		<< "\n\tThis continues til a player  successfully locates all their opponent’s ships first by hitting"
		<< "\n\teach square they occupy and then he is declared the winner as soon as all ships have been destroyed." << endl;
	cout << "\nScoring: "
		<< "\n\n\t Hit  						1 Point"
		<< "\n\t Miss						-0.25 Points"
		<< "\n\t Sink Aircraft Carrier				10 Points"
		<< "\n\t Sink Battleship				8 Points"
		<< "\n\t Sink Cruiser					6 Points"
		<< "\n\t Sink Submarine					6 Points"
		<< "\n\t Sink Destroyer					4 Points";
}
void credits()
{
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Made by:\n" << endl;
	//SetConsoleTextAttribute(handle, 5 | FOREGROUND_INTENSITY);
}