/*
 * write.c: Handle write syscall.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:52 PM
 */

#include <exports.h>
#include <bits/errno.h>
#include <bits/fileno.h>

ssize_t write (int fd, const void *buf, size_t count)
{
	char *cbuf = (char *)buf;
	int i;

	if (fd != STDOUT_FILENO)
	{
		printf("Error: wrong file number\n");
		return -EBADF;
	}
	if ((unsigned)cbuf < 0xa0000000 
		|| ((unsigned)cbuf + count > 0xa3ffffff))
	{
		printf("Error: bad address\n");		
		return -EFAULT;
	}

	for (i = 0; i < (int)count && cbuf[i] != '\0'; i ++)
	{
		putc(cbuf[i]);
	}
	putc('\n');

	return i;
}
