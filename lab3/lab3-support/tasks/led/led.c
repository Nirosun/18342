/** @file led.c
 *
 * @brief print two ascii arts ("hello" and "")
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define PIC_SIZE 1024
#define ESC 0x1B
#define BRACKET 0x5B


int main(int argc, char** argv)
{
	char pic_1[PIC_SIZE] = 	" _    _          _   _                         \n" 
			       	"| |  | |        | | | |                        \n" 
			       	"| |__| |   ___  | | | |   ___                  \n"
			       	"|  __  |  / _ \\ | | | |  / _ \\               \n"
			       	"| |  | | |  __/ | | | | | (_) |                \n"
				"|_|  |_|  \\___| |_| |_|  \\___/               \n";
	char pic_2[PIC_SIZE] =  " __          __                 _       _      \n"
				" \\ \\        / /                | |     | |   \n"
				"  \\ \\  /\\  / /    ___    _ __  | |   __| |  \n"
				"   \\ \\/  \\/ /    / _ \\  | '__| | |  / _` | \n"
				"    \\  /\\  /    | (_) | | |    | | | (_| |   \n"
				"     \\/  \\/      \\___/  |_|    |_|  \\__,_| \n";
	
	
	int i;
	for (i = 0; i < 10; i ++)
	{
		write(STDOUT_FILENO, pic_1, PIC_SIZE);
		sleep(100);
		printf("%c%c6A", 0x1b, 0x5b);
		write(STDOUT_FILENO, pic_2, PIC_SIZE);
		sleep(100);
		printf("%c%c6A", 0x1b, 0x5b);
	}	
	
	return 0;
}
