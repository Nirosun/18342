/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Group Member 1 <email address>
 *          Group Member 2 <email address>
 * Date:    The current time & date
 */
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 1000

int main(int argc, char *argv[]) {
	/* Needs more code. */
	//const char *err = "Error\n";
	/*int tmp;
	tmp = write(STDOUT_FILENO, (void *)argv[0], MAX_SIZE);
	if (tmp < 0) {
		exit(-1);
		//write(STDOUT_FILENO, err, MAX_SIZE);
	}
	write(STDOUT_FILENO, argv[1], MAX_SIZE);
*/

	int count_read, count_write = -1, i;
	char buf[MAX_SIZE];
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
		while (count_write != count_read)
		{
			count_write = write(STDOUT_FILENO, buf, count_read);
			if (count_write < 0)
			{
				exit(1);
			}
		}
		count_write = -1;
	}

	return 0;
}
