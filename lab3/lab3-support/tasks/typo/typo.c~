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


int main(int argc, char** argv)
{
	int count_read, count_write, count_ret=0;
	char buf[1024], *ptr;
	unsigned long start_time = 0;
	unsigned long input_time = 0;
	char prompt[50] = "Please input:\n";
	//char timeInt[10];
	//char timeFrac[10];
	//int count_itoa;

	while (1)
	{
		start_time = time();
		//printf("%lu\n", start_time);
		write(STDOUT_FILENO, prompt, 1024);
		count_read = read(STDIN_FILENO, buf, 10);
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
		
		write(STDOUT_FILENO, "\n", 10);	
		
		input_time = time() - start_time;

		input_time = input_time / 100;
		//timeFrac[0] = 
		//start_time = time();
		
		/*count_itoa = 0;
		do{
       			timeStr[count_itoa++] = input_time % 10 + '0';
		}while ((input_time/=10) > 0);

		write(STDOUT_FILENO, timeStr, 1024);*/

		printf("%lu\n", input_time);
		count_write = -1;
	}
	return 0;
}
