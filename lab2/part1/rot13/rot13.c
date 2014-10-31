/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:    10/06/2014, 2:25 PM
 */
#include <stdlib.h>
#include <unistd.h>
#include <exports.h>

#define MAX_SIZE 1000

int main(void) {

	int count_read, count_write, count_ret=0, i;
	char buf[MAX_SIZE], *ptr;
	while (1)
	{
		count_read = read(STDIN_FILENO, buf, MAX_SIZE);
		if (count_read < 0)
		{
			exit(1);
		}
		for (i = 0; i < count_read; i ++)
		{
			if ((buf[i] >= 65 && buf[i] <= 77) ||
				(buf[i] >= 97 && buf[i] <= 109))
			{
				buf[i] += 13;
			}
			else if ((buf[i] >= 78 && buf[i] <=90) ||
				(buf[i] >= 110 && buf[i] <= 122))
			{
				buf[i] -= 13;
			}
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
	}

	return 0;
}
