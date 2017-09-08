#include "Battleship3.h"

void display_menu (void)
{
	/*
	Function: display_menu (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Prints out the main menu screen
	Input parameters: None
	Returns: None
	Preconditions: None
	Postconditions: The menu is displayed on the screen
	*/
	
	printf ("**********WELCOME TO BATTLESHIP**********\n\n");
	printf ("Select an option:\n\n");
	printf ("	1. Display game rules.\n");
	printf ("	2. Play game.\n");
	printf ("	3. Quit game.\n\n");
	printf ("*****************************************\n\n");
}

int is_valid_option (void)
{
	/*
	Function: int is_valid_option (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Checks to see if user input on the menu screen is valid
	Input parameters: None
	Returns: Whether the input was valid or not
	Preconditions: The menu is on display
	Postconditions: The user has entered a valid input
	*/
	
	int option = 0;

	//clear screen and display menu until valid option is entered
	do
	{
		system ("cls");
		
		display_menu ();

		scanf ("%d", &option);
	}while ((option < 1) || (option > 3)); //indicates that this code will repeat until valid option is entered

	return option;
}

void print_game_rules (void)
{
	/*
	Function: void print_game_rules (void) 
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Prints out the rules of the game to the user
	Input parameters: None
	Returns: None
	Preconditions: Option 1 was slected from the menu screen
	Postconditions: The rules have been displayed
	*/

	system ("cls");

	printf ("**********WELCOME TO BATTLESHIP**********\n\n");
	printf ("RULES OF THE GAME:\n\n");
	printf ("-- Each player has 5 ships of different length arranged on a 10x10 playing board\n");
	printf ("\tCarrier: 5 cells.\n");
	printf ("\tBattleship: 4 cells.\n");
	printf ("\tCruiser: 3 cells.\n");
	printf ("\tSubmarine: 3 cells.\n");
	printf ("\tDestroyer: 2 cells.\n\n");
	printf ("-- Each player will take turns guessing where the other player's ship is located\n");
	printf ("-- If they have made a correct guess, that counts as a hit on the ship\n");
	printf ("-- Each ship can take as many hits as it is long\n");
	printf ("-- Once one player has sunk all of the opponent's ships, they have won the game\n\n");
	printf ("*****************************************\n\n");

	system ("pause");
	system ("cls");
	eval_user_options();
}

void quit_game (void)
{
	/*
	Function: void quit_game (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Takes the user out of the game program
	Input parameters: None
	Returns: None
	Preconditions: Option 3 has been chosen from the menu screen
	Postconditions: The game will be exited
	*/
	
	char option = '\0';

	system ("cls");
	
	printf ("Thanks for playing. Bye.\n\n");

	exit (0);
}

void init_board (char board[][MAX_COLS], int rows, int cols)
{
	/*
	Function: void init_board (char board[][MAX_COLS], int rows, int cols)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Assigns every place on the board a '~' to represent it
	Input parameters: The 2D array for the board, number of rows, number of columns
	Returns: None
	Preconditions: The game is being set up
	Postconditions: The board has been initialized
	*/
	
	int index_row = 0, index_col = 0;

	for (index_row = 0; index_row < rows; index_row++)
	{
		//for every row, initialize the row, column pair
		for (index_col = 0; index_col < cols; index_col++)
		{
			board[index_row][index_col] = '~';
		}
	}
}

void print_board (char board[][MAX_COLS], int rows, int cols)
{
	/*
	Function: void print_board (char board[][MAX_COLS], int rows, int cols)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Prints out the desired board
	Input parameters: The board to be printed, number of rows, number of columns
	Returns: None
	Preconditions: The boards have been initialized and properly altered otherwise
	Postconditions: The board is printed to the screen
	*/
	
	int index_row = 0, index_col = 0;

	printf ("   1 2 3 4 5 6 7 8 9 10\n");
	for (index_row = 0; index_row < rows; index_row++)
	{
		if (index_row < 9)
		{
			printf("%d ", index_row + 1);
		}
		else
		{
			printf("%d", index_row + 1);
		}

		//for every row, initialize the row, column pair
		for (index_col = 0; index_col < cols; index_col++)
		{
			//board[index_row][index_col] = '~';
			printf (" %c", board[index_row][index_col]);
		}

		putchar ('\n'); //prints the newline character 
	}
}

int generate_dir (void)
{
	/*
	Function: int generate_dir (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Decides which direction the ship will be oriented
	Input parameters: None
	Returns: The direction of the ship
	Preconditions: None
	Postconditions: The direction for a ship is chosen
	*/
	
	int dir = 0;

	//0 - horizontal direction, 1 - vertical direction
	dir = rand() % 2; //gives us back 0 and 1

	return dir;
}

void generate_start_pt (int dir, int ship_length, int *row_start, int *col_start)
{
	/*
	Function: void generate_start_pt (int dir, int ship_length, int *row_start, int *col_start)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Decides which point on the board the ship's placement will start at
	Input parameters: Direction of ship, length of ship, pointers to the starting point (row and column)
	Returns: None
	Preconditions: A direction and length of the ship are known
	Postconditions: The start point for the ship is chosen
	*/

	//vertical
	if (dir == 1) //ensures that the ship won't go off the board
	{
		*col_start = rand() % MAX_COLS;
		*row_start = rand() % (MAX_ROWS - ship_length + 1); //this might be problematic?????
	}
	//horizontal
	else //ensures that the ship won't go off the board
	{
		*row_start = rand() % MAX_ROWS;
		*col_start = rand() % (MAX_COLS - ship_length + 1);
	}
}

void place_ship (char board[][MAX_COLS], Ship ship_info, int *row_start, int *col_start)
{
	/*
	Function: void place_ship (char board[][MAX_COLS], Ship ship_info, int *row_start, int *col_start)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Places the ship on the board
	Input parameters: The board to put the ship on, information about the ship, the starting point for the ship
	Returns: None
	Preconditions: The desired ship is known
	Postconditions: The ship is placed on the board
	*/
	
	int index = 0, dir = 0, length = 0;
	char name = '\0';
	
	ship_info.direction = generate_dir();
	dir = ship_info.direction;
	length = ship_info.length;
	name = ship_info.letter_name;

	generate_start_pt (dir, length, row_start, col_start);

	if (dir == 1) //vertical
	{
		for (index = 0; index < length; index++)
		{
			board[*row_start + index][*col_start] = name;
		}
	}
	else //horizontal
	{
		for (index = 0; index < length; index++)
		{
			board[*row_start][*col_start + index] = name;
		}
	}
}

int is_ship_sunk (Ship ship_info)
{
	/*
	Function: int is_ship_sunk (Ship ship_info)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Determines whether or not a ship has been sunk
	Input parameters: Information for the ship
	Returns: Whether or not the ship was sunk
	Preconditions: The ship is known 
	Postconditions: It is known whether or not the ship was sunk
	*/
	
	int sunk = 0;
	
	if (ship_info.hits == ship_info.length)
	{
		sunk = 1;
	}
	else
	{
		sunk = 0;
	}

	return sunk;
}

int target_comp_board (char board_target[][MAX_COLS], char board_visible[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer)
{
	/*
	Function: int target_comp_board (char board_target[][MAX_COLS], char board_visible[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Goes through gameplay that allows the user to target ships on the computer's board
	Input parameters: The computer's board with its ships, what the user can see of the computer's board, information on all of the ships
	Returns: The total number of hits the user has gotten on the computer's ships
	Preconditions: Gameplay has started
	Postconditions: The user has completed one turn on the computer
	*/
	
	int row_target = 0, col_target = 0, sunk = 0, total_hits = 0;

	system ("cls");
	printf ("This is the computer's board:\n\n");
	print_board (board_visible, MAX_ROWS, MAX_COLS);
	printf ("Which row would you like to target?: ");
	scanf ("%d", &row_target);
	printf ("Which column would you like to target?: ");
	scanf ("%d", &col_target);

	if ((board_target[row_target - 1][col_target - 1] != '~') && (board_target[row_target - 1][col_target - 1] != 'X'))
	{
		system ("cls");
		
		if (board_target[row_target - 1][col_target - 1] == 'C')
		{
			printf ("You have hit the carrier!\n\n");
			board_target[row_target - 1][col_target - 1] = 'X';
			board_visible[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (carrier);
			if (sunk == 1)
			{
				printf ("You have sunk the carrier!\n\n");
			}
		}
		if (board_target[row_target - 1][col_target - 1] == 'B')
		{
			printf ("You have hit the battleship!\n\n");
			board_target[row_target - 1][col_target - 1] = 'X';
			board_visible[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (battleship);
			if (sunk == 1)
			{
				printf ("You have sunk the battleship!\n\n");
			}
		}
		if (board_target[row_target - 1][col_target - 1] == 'R')
		{
			printf ("You have hit the cruiser!\n\n");
			board_target[row_target - 1][col_target - 1] = 'X';
			board_visible[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (cruiser);
			if (sunk == 1)
			{
				printf ("You have sunk the cruiser!\n\n");
			}
		}
		if (board_target[row_target - 1][col_target - 1] == 'S')
		{
			printf ("You have hit the submarine!\n\n");
			board_target[row_target - 1][col_target - 1] = 'X';
			board_visible[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (sub);
			if (sunk == 1)
			{
				printf ("You have sunk the submarine!\n\n");
			}
		}
		if (board_target[row_target - 1][col_target - 1] == 'D')
		{
			printf ("You have hit the destroyer!\n\n");
			board_target[row_target - 1][col_target - 1] = 'X';
			board_visible[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (destroyer);
			if (sunk == 1)
			{
				printf ("You have sunk the destroyer!\n\n");
			}
		}

		total_hits += 1;
	}
	else
	{
		system ("cls");
		
		printf ("You missed! Try again.\n\n");
		board_visible[row_target - 1][col_target - 1] = '*';
	}

	print_board (board_visible, MAX_ROWS, MAX_COLS);
	system ("pause");

	return total_hits;
}

int target_player_board (char board[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer)
{
	/*
	Function: int target_player_board (char board[][MAX_COLS], Ship carrier, Ship battleship, Ship cruiser, Ship sub, Ship destroyer)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Goes through gameplay that shows what moves the computer took against the user
	Input parameters: The player's board, and information on all of their ships
	Returns: The total number of hits the computer has gotten on the user's ships
	Preconditions: Gameplay has started
	Postconditions: The computer has completed a round on the user
	*/
	
	int row_target = 0, col_target = 0, sunk = 0, total_hits = 0;

	row_target = rand() % MAX_ROWS;
	col_target = rand() % MAX_COLS;

	if ((board[row_target - 1][col_target - 1] != '~') && (board[row_target - 1][col_target - 1] != 'X'))
	{
		system ("cls");
		
		if (board[row_target - 1][col_target - 1] == 'C')
		{
			printf ("The computer hit your carrier!\n\n");
			board[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (carrier);
			if (sunk == 1)
			{
				printf ("The computer sunk your carrier!\n\n");
			}
		}
		if (board[row_target - 1][col_target - 1] == 'B')
		{
			printf ("The computer hit your battleship!\n\n");
			board[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (battleship);
			if (sunk == 1)
			{
				printf ("The computer sunk your battleship!\n\n");
			}
		}
		if (board[row_target - 1][col_target - 1] == 'R')
		{
			printf ("The computer hit your cruiser!\n\n");
			board[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (cruiser);
			if (sunk == 1)
			{
				printf ("The computer sunk your cruiser!\n\n");
			}
		}
		if (board[row_target - 1][col_target - 1] == 'S')
		{
			printf ("The computer hit your submarine!\n\n");
			board[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (sub);
			if (sunk == 1)
			{
				printf ("The computer sunk your submarine!\n\n");
			}
		}
		if (board[row_target - 1][col_target - 1] == 'D')
		{
			printf ("The computer hit your destroyer!\n\n");
			board[row_target - 1][col_target - 1] = 'X';
			carrier.hits += 1;
			sunk = is_ship_sunk (destroyer);
			if (sunk == 1)
			{
				printf ("The computer sunk your destroyer!\n\n");
			}
		}

		total_hits += 1;
	}
	else
	{
		system ("cls");
		
		printf ("The computer missed!\n\n");
		board[row_target - 1][col_target - 1] = '*';
	}

	print_board (board, MAX_ROWS, MAX_COLS);
	system ("pause");

	return total_hits;
}

void gameplay (void)
{
	/*
	Function: void gameplay (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Runs through entire gameplay, including the determination of who has won
	Input parameters: None
	Returns: None
	Preconditions: Option 2 has been chosen from the menu
	Postconditions: Gameplay has taken place
	*/
	
	char board_p1[MAX_ROWS][MAX_COLS], board_comp[MAX_ROWS][MAX_COLS], board_comp_visible[MAX_ROWS][MAX_COLS];
	int row_start = 1, col_start = 1, total_hits_p1 = 0, total_hits_comp = 0;
	Ship carrier_p1 = {0, 5, 'C'}, battleship_p1 = {0, 4, 'B'}, cruiser_p1 = {0, 3, 'R'}, submarine_p1 = {0, 3, 'S'}, destroyer_p1 = {0, 2, 'D'};
	Ship carrier_comp = {0, 5, 'C'}, battleship_comp = {0, 4, 'B'}, cruiser_comp = {0, 3, 'R'}, submarine_comp = {0, 3, 'S'}, destroyer_comp = {0, 2, 'D'};
	
	init_board (board_p1, MAX_ROWS, MAX_COLS);
	init_board (board_comp, MAX_ROWS, MAX_COLS);
	init_board (board_comp_visible, MAX_ROWS, MAX_COLS);

	place_ship (board_p1, carrier_p1, &row_start, &col_start);
	place_ship (board_p1, battleship_p1, &row_start, &col_start);
	place_ship (board_p1, cruiser_p1, &row_start, &col_start);
	place_ship (board_p1, submarine_p1, &row_start, &col_start);
	place_ship (board_p1, destroyer_p1, &row_start, &col_start);

	place_ship (board_comp, carrier_comp, &row_start, &col_start);
	place_ship (board_comp, battleship_comp, &row_start, &col_start);
	place_ship (board_comp, cruiser_comp, &row_start, &col_start);
	place_ship (board_comp, submarine_comp, &row_start, &col_start);
	place_ship (board_comp, destroyer_comp, &row_start, &col_start);
	
	printf ("You are going to start first.\n");
	printf ("This is where the ships on your board have been placed: \n\n");
	print_board (board_p1, MAX_ROWS, MAX_COLS);
	system ("pause");
	system ("cls");

	do
	{
		total_hits_p1 = target_comp_board (board_comp, board_comp_visible, carrier_comp, battleship_comp, cruiser_comp, submarine_comp, destroyer_comp);
		total_hits_comp = target_player_board (board_p1, carrier_p1, battleship_p1, cruiser_p1, submarine_p1, destroyer_p1);

	} while ((total_hits_p1 < 17) && (total_hits_comp < 17));

	if (total_hits_p1 == 17)
	{
		system ("pause");
		system ("cls");
		printf ("Congratulations, you won!\n\n");
	}
	if (total_hits_comp == 17)
	{
		system ("pause");
		system ("cls");
		printf ("Sorry, the computer won.\n\n");
	}

	system ("pause");
	eval_user_options();
}

void eval_user_options (void)
{
	/*
	Function: void eval_user_options (void)
	Date created: March 23, 2015
	Date last modified: April 5, 2015
	Description: Gets the user's selection for what option they want from the menu screen and runs the corresponding functions
	Input parameters: None
	Returns: None
	Preconditions: The menu is on display
	Postconditions: An option has been chosen and its corresponding function is running
	*/
	
	int option = 0;
	
	display_menu();
	option = is_valid_option();
	
	if (option == 1)
	{
		print_game_rules();
	}
	if (option == 2)
	{
		system ("cls");
		gameplay();
	}
	if (option == 3)
	{
		quit_game();
	}
}
