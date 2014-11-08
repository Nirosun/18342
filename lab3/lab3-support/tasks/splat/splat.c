/*
 * splat.c: Displays a spinning cursor.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 *         Yang Wu <yangwu@andrew.cmu.edu>
 * Date:   Fri, 7 Nov 2014 08:56 PM
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
