/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	while(1)
	{
		write(STDOUT_FILENO, "\r|",2);
		sleep(200);
		write(STDOUT_FILENO, "\r/",2);
		sleep(200);
		write(STDOUT_FILENO, "\r-",2);
		sleep(200);
		write(STDOUT_FILENO, "\r\\",2);
		sleep(200);
	}
	return 0;
}
