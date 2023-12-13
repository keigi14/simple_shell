#include "main.h"

/**
 * _c_lang_puts - prints an input strng given.
 * @mi_stg: the str to be printed
 * Return: empty
 */
void _c_lang_puts(char *mi_stg)
{
	int v = 0;

	if (!mi_stg)
		return;
	while (mi_stg[v] != '\0')
	{
		_c_lang_putchar(mi_stg[v]);
		v++;
	}
}

/**
 * _c_lang_putchar - write charactr c to std err.
 * @c: a char to be printed
 * Return: success 1.
 * if error, -1 is returned, and errno is set appropriately.
 */
int _c_lang_putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int k;

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _put_fld - writes char c to given fd
 * @c: the char to be printed
 * @fd: the file descriptor to write to
 * Return: On success 1
 * if error, -1 is returned, errno is set appropriately
 */
int _put_fld(char c, int fd)
{
	static int k;

	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _puts_fld - it prints an input str
 * @mi_stg: the str to be printed
 * @fild: the file descriptor to write to
 * Return: the nubr of chars put
 */
int _puts_fld(char *mi_stg, int fild)
{
	int z = 0;

	if (!mi_stg)
		return (0);
	while (*mi_stg)
	{
		z += _put_fld(*mi_stg++, fild);
	}
	return (z);
}
