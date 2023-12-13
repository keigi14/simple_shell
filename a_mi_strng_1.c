#include "main.h"

/**
 * _strngs_cpy - copies a str
 * @destin: the destination it goes
 * @sorc: that source
 * Return: ptr to destination
 */
char *_strngs_cpy(char *destin, char *sorc)
{
	int t = 0;

	if (destin == sorc || sorc == 0)
		return (destin);
	while (sorc[t])
	{
		destin[t] = sorc[t];
		t++;
	}
	destin[t] = 0;
	return (destin);
}

/**
 * _string_dupo - double a str
 * @mi_stg: a mi_stg to duplicate
 * Return: ptr to  duplicated str
 */
char *_string_dupo(const char *mi_stg)
{
	char *ret;
	int leng = 0;

	if (mi_stg == NULL)
		return (NULL);
	while (*mi_stg++)
		leng++;
	ret = malloc(sizeof(char) * (leng + 1));
	if (!ret)
		return (NULL);
	for (leng++; leng--;)
		ret[leng] = *--mi_stg;
	return (ret);
}

/**
 * _dis_puts - prints an input str
 * @mi_stg: the str to be printed
 * Return: Noting
 */
void _dis_puts(char *mi_stg)
{
	int v = 0;

	if (!mi_stg)
		return;
	while (mi_stg[v] != '\0')
	{
		_o_puchar(mi_stg[v]);
		v++;
	}
}

/**
 * _o_puchar - writes the char c to stdout.
 * @c: the char to print
 * Return: 1 as success
 * On error, -1 is returned, and errno is set appropriately.
 */
int _o_puchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int v;

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(1, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}
