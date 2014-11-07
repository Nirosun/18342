/** @file led.c
 *
 * @brief 
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//#include <types.h>

#define LINE_SIZE 30
#define LINES 6
#define PIC_SIZE 1024

int main(int argc, char** argv)
{
	char pic_1[PIC_SIZE] = 		 " _    _          _   _         \n" 
					 "| |  | |        | | | |        \n" 
					 "| |__| |   ___  | | | |   ___  \n"
					 "|  __  |  / _ \\ | | | |  / _ \\ \n"
					 "| |  | | |  __/ | | | | | (_) |\n"
					 "|_|  |_|  \\___| |_| |_|  \\___/ ";
	char pic_null[PIC_SIZE] = {"\r"};
	//char onechar[2] = "\0\0";	
	
	int i;
	for (i = 0; i < 10; i ++)
	{
		write(STDOUT_FILENO, pic_1, PIC_SIZE);
		sleep(100);
		write(STDOUT_FILENO, pic_null, PIC_SIZE);
		sleep(100);
	}	
	
	return 0;
}
