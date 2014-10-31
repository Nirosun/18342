/*
 * read.c: Handle read syscall.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:51 PM
 */

#include <exports.h>
#include <bits/errno.h>
#include <bits/fileno.h>

ssize_t read (int fd, void *buf, size_t count)
{
	
	char *cbuf = (char *)buf;

	if (fd != STDIN_FILENO)
	{
		printf("Error: wrong file number\n");
		return -EBADF;
	}
	if ((unsigned)cbuf < 0xa0000000 || ((unsigned)cbuf + count > 0xa3ffffff))
	{
		printf("Error: bad address\n");		
		return -EFAULT;
	}
	
	int id = 0;
	while (1)
	{
		if (id >= count)
		{
			cbuf[id] = '\0';
			putc('\n');
			return id;
		}		
		if (tstc())
		{
			char c = (char)getc();
			if (c == 4)	// EOT character
			{
				cbuf[id] = '\0';
				putc('\n');
				return id;
			}
			else if (c == 8 || c == 127)	// backspace or delete
			{
				if (id == 0)
				{
					continue;
				}
				id --;
				cbuf[id--] = '\0';
				//id --;
				putc('\b');
				putc(' ');
				putc('\b');
			}
			else if (c == 10 || c == 13)	// newline or carriage return
			{
				cbuf[id] = c;
				id ++;
				cbuf[id] = '\0';
				putc('\n');
				return id;
			}
			else
			{
				cbuf[id] = c;
				putc(c);
			}
			id ++;
		}
	}

	return 0;
}
