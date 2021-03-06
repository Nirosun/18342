/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//#include <types.h>

#define BUF_SIZE 1024
#define LINE_SIZE 30

int main(int argc, char** argv)
{ 
	int count_read, count_write, count_ret=0;
	char buf[BUF_SIZE], *ptr;
	unsigned long start_time = 0;
	unsigned long input_time = 0;
	char prompt[LINE_SIZE] = "> ";

	while (1)
	{
		start_time = time();
		write(STDOUT_FILENO, prompt, LINE_SIZE);

		// echo characters
		count_read = read(STDIN_FILENO, buf, LINE_SIZE);
		if (count_read < 0)
		{
			exit(1);
		}
		
		count_write = 0;
		ptr = &buf[0];
		do
		{
			count_ret = write(STDOUT_FILENO, ptr, count_read - count_write);
			if (count_ret < 0)
			{
				exit(1);
			}
			count_write += count_ret;
			ptr = &buf[count_write];
		} while (count_write != count_read);
		count_write = -1;
		write(STDOUT_FILENO, "\n", LINE_SIZE);	
		
		// calculate and print time
		input_time = time() - start_time;
		input_time = input_time / 100;
		
		int count_itoa = 0;	// length of string that shows time
		char timeStr[LINE_SIZE];	// string that shows time
		char timeInt[LINE_SIZE];	// integer part of time
		char timeFrac[LINE_SIZE];	// fraction part of time
		
		// transfer time to strings for output
		do
		{
       			timeStr[count_itoa++] = input_time % 10 + '0';
		}while ((input_time /= 10) > 0);
		timeStr[count_itoa] = '\0';
		
		if (count_itoa == 1)
		{
			timeInt[0] = '0';
			timeInt[1] = '\0';
			timeFrac[0] = timeStr[0];
			timeFrac[1] = '\0';
		}
		else {
			int i;
			for (i = count_itoa - 1; i > 0; i --) 
			{
				timeInt[count_itoa-1-i] = timeStr[i];
			}
			timeInt[count_itoa-1] = '\0';
			timeFrac[0] = timeStr[0];
			timeFrac[1] = '\0';
		}
		
		write(STDOUT_FILENO, timeInt, LINE_SIZE);
		write(STDOUT_FILENO, ".", LINE_SIZE);
		write(STDOUT_FILENO, timeFrac, LINE_SIZE);		
		write(STDOUT_FILENO, "s\n", LINE_SIZE);
	}
	return 0;
}
