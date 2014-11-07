/** @file tictactoe.c
 *
 * @brief Play tic-tac-toe
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//#include <types.h>

#define LINE_SIZE 80
#define TIME_LIMIT 10

int main(int argc, char** argv)
{
	write(STDOUT_FILENO, "This is a tic-tac-toe game, have fun.\n", 50);

	char grid[5][LINE_SIZE] = {"   |   |   \n",
			   "---+---+---\n",
                           "   |   |   \n",
                           "---+---+---\n",
                           "   |   |   \n"};
	char cnum[LINE_SIZE] = "0";
	int xs[9] = {0};
	int os[9] = {0};
	int rounds = 1;
	int isEnd = 0;
	int isOverTime = 0;
	unsigned long time_limit = TIME_LIMIT;

	while (isEnd == 0)
	{
		int playID = (rounds % 2 == 1) ? 1 : 2;
		int isCorrectInput = 0;
		unsigned long time_start = time() / 1000;
		unsigned long time_input = 0;

		printf("**** Player %d ****\n", playID);
		printf("The time limit for this round is: %lus\n", time_limit);
		while (!isCorrectInput)
		{
			write(STDOUT_FILENO, "Please input a number: ", LINE_SIZE);
			read(STDIN_FILENO, cnum, LINE_SIZE);

			if (cnum[0] >= '1' && cnum[0] <= '9')
			{
				if (xs[cnum[0]-'1'] || os[cnum[0]-'1'])
				{
					write(STDOUT_FILENO, "The position is already occupied! Please input again.\n", LINE_SIZE);
					continue;					
				}
				isCorrectInput = 1;
			}
			else 
			{
				write(STDOUT_FILENO, "Wrong input! Please input again.\n", LINE_SIZE);
				continue;
			}

			time_input = time() / 1000 - time_start;
			printf("You used %lus for this round.\n", time_input);
			
			if (time_input > time_limit)
			{
				printf("You exceed the time limit of %lus!\n", time_limit);
				isOverTime = 1;
				break;
			}

			char mark = (rounds % 2 == 0) ? 'x' : 'o';
			if (rounds % 2 == 0)
			{
				mark = 'x';
				xs[cnum[0] - '1'] = 1;
			}
			else
			{
				mark = 'o';
				os[cnum[0] - '1'] = 1;
			}

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
		
		if (isOverTime != 0)
		{
			printf("Player %d wins. Game ends.\n", (playID == 1) ? 2 : 1);
			break;
		}

		int i;
		for (i = 0; i < 5; i ++)
		{
			write(STDOUT_FILENO, grid[i], LINE_SIZE);
		}

		rounds ++;
		if (rounds == 10) 
		{
			printf("Draw. Game ends.\n");
			break;			
		}
	}
	//write(STDOUT_FILENO, "Game ends.\n", LINE_SIZE);

	//write(STDOUT_FILENO, grid, 50);
	//write(STDOUT_FILENO, "what's the wierd staff...\n", LINE_SIZE);

	return 0;
}
