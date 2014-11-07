/** @file tictactoe.c
 *
 * @brief Play the tic-tac-toe game. The system calls (read, 
 * write, sleep, time) are used in this program. This game is 
 * designed for two players. In every round the player input a
 * number to indicate in which grid he/she wants to put a naught 
 * or cross. 
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define LINE_SIZE 80
#define TIME_LIMIT 20

int main(int argc, char** argv)
{

	char grid[5][LINE_SIZE] = {"   |   |   \n",
			   "---+---+---\n",
                           "   |   |   \n",
                           "---+---+---\n",
                           "   |   |   \n"};
	char gridExample[5][LINE_SIZE] = {" 1 | 2 | 3 \n",
			   "---+---+---\n",
                           " 4 | 5 | 6 \n",
                           "---+---+---\n",
                           " 7 | 8 | 9 \n"};
	int xandos[2][9] = {{0}, {0}};	// mark if grids are marked as 'x' or 'o'
	int rounds = 1;	 
	int j;
	unsigned long time_limit = TIME_LIMIT;	

	write(STDOUT_FILENO, "This is a tic-tac-toe game.\n", LINE_SIZE);
	write(STDOUT_FILENO, "The example of input number is: \n", LINE_SIZE);
	for (j = 0; j < 5; j ++)
	{
		write(STDOUT_FILENO, gridExample[j], LINE_SIZE);
	}	
	write(STDOUT_FILENO, "The game will begin in 3 seconds.\n", LINE_SIZE);

	sleep (300);	// 3 seconds for preparing :)

	while (1)
	{
		int playID = (rounds % 2 == 1) ? 1 : 2;
		int id = playID - 1;
		int isCorrectInput = 0;
		int isOverTime = 0;	// if the player exceeds the time limit
		int isWin = 0;		// does the player wins in this round
		int i;		
		unsigned long time_start = time() / 1000;
		unsigned long time_input = 0;
		char cnum[LINE_SIZE] = "0";

		printf("**** Player %d ****\n", playID);
		printf("The time limit for this round is: %lus\n", time_limit);
		while (!isCorrectInput)
		{
			write(STDOUT_FILENO, "Please input a number: ", LINE_SIZE);
			read(STDIN_FILENO, cnum, LINE_SIZE);

			if (cnum[0] >= '1' && cnum[0] <= '9')
			{
				if (xandos[0][cnum[0]-'1'] || xandos[1][cnum[0]-'1'])
				{
					write(STDOUT_FILENO, "Position already occupied! Please input again.\n", LINE_SIZE);
					continue;					
				}
				isCorrectInput = 1;
			}
			else 
			{
				write(STDOUT_FILENO, "Wrong input! Please input again.\n", LINE_SIZE);
				continue;
			}

			time_input = time() / 1000 - time_start;	// time the user spent in one round
			printf("You used %lus for this round.\n", time_input);
			
			if (time_input > time_limit)
			{
				printf("You exceed the time limit of %lus!\n", time_limit);
				isOverTime = 1;
				break;
			}
			
			// mark 'x' or 'o' in grid
			char mark = (playID == 1) ? 'x' : 'o';
			xandos[id][cnum[0]-'1'] = 1;
			switch (cnum[0])
			{
			case '1':
				grid[0][1] = mark;
				break;
			case '2':
				grid[0][5] = mark;
				break;
			case '3':
				grid[0][9] = mark;
				break;
			case '4':
				grid[2][1] = mark;
				break;
			case '5':
				grid[2][5] = mark;
				break;
			case '6':
				grid[2][9] = mark;
				break;
			case '7':
				grid[4][1] = mark;
				break;
			case '8':
				grid[4][5] = mark;
				break;
			case '9':
				grid[4][9] = mark;
				break;
			default:
				write(STDOUT_FILENO, "Shouldn't come here.\n", LINE_SIZE);
			}
		}
		
		if (isOverTime)
		{
			printf("Player %d wins. Game ends.\n", (playID == 1) ? 2 : 1);
			break;
		}

		for (i = 0; i < 5; i ++)
		{
			write(STDOUT_FILENO, grid[i], LINE_SIZE);
		}
		
		// check if the player wins
		for (i = 0; i < 9; i += 3)
		{
			if (xandos[id][i] && xandos[id][i+1] && xandos[id][i+2])
			{
				isWin = 1;
				break;
			}
		}
		if (!isWin) {
			for (i = 0; i < 3; i ++)
			{
				if (xandos[id][i] && xandos[id][i+3] && xandos[id][i+6])
				{
					isWin = 1;
					break;
				}
			}
		}
		if (!isWin && ((xandos[id][0] && xandos[id][4] && xandos[id][8]) 
			|| (xandos[id][2] && xandos[id][4] && xandos[id][6])))
		{
			isWin = 1;
		}

		if (isWin)
		{
			printf("Player %d wins! Game ends.\n", playID);
			break;
		}

		rounds ++;
		if (rounds == 10) 
		{
			printf("Draw. Game ends.\n");
			break;			
		}
	}

	return 0;
}
