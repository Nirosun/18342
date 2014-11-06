/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */
#include <bits/fileno.h>
#include <stdlib.h>
#include <unistd.h>
#include <types.h>


int main(int argc, char** argv)
{
	int count_read, count_write, count_ret=0;
	char buf[1024], *ptr;
	size_t start_time = time();

	while (1)
	{
		count_read = read(STDIN_FILENO, buf, 1024);
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
		write(STDOUT_FILENO,);
		count_write = -1;
	}
	return 0;
}
