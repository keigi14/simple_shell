#include "main.h"

/**
 * de_erro_toi - converts a strg to an int.
 * @s: de str to be converted
 * Return: 0 if no nubrs in str, converted nubr ifnot
 * -1 on error
 */
int de_erro_toi(char *s)
{
	int d = 0;
	unsigned long int rezurt = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (d = 0;  s[d] != '\0'; d++)
	{
		if (s[d] >= '0' && s[d] <= '9')
		{
			rezurt *= 10;
			rezurt += (s[d] - '0');
			if (rezurt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rezurt);
}

/**
 * _pr_error - prints an error messages
 * @info: de paramter and return info structur.
 * @errstr: str containing specified error type
 * Return: 0 if no nubers in str, converted nubr ifnot
 * -1 on error
 */
void _pr_error(mi_info_on *info, char *errstr)
{
	_c_lang_puts(info->p_fl_nm);
	_c_lang_puts(": ");
	_pr_dec(info->row_countn, STDERR_FILENO);
	_c_lang_puts(": ");
	_c_lang_puts(info->de_av[0]);
	_c_lang_puts(": ");
	_c_lang_puts(errstr);
}

/**
 * _pr_dec - this func prints adecimal(integer) nubr (base 10)
 * @input: de input
 * @fd: the file descriptor to write to
 *
 * Return: nuber of characters printed
 */
int _pr_dec(int input, int fd)
{
	unsigned int _alp_, current;
	int v;
	int count = 0;
	int (*__o_puchar)(char) = _o_puchar;

	if (fd == STDERR_FILENO)
		__o_puchar = _c_lang_putchar;
	if (input < 0)
	{
		_alp_ = -input;
		__o_puchar('-');
		count++;
	}
	else
		_alp_ = input;
	current = _alp_;
	for (v = 1000000000; v > 1; v /= 10)
	{
		if (_alp_ / v)
		{
			__o_puchar('0' + current / v);
			count++;
		}
		current %= v;
	}
	__o_puchar('0' + current);
	count++;

	return (count);
}

/**
 * _trans_nubr - converter func, a clone of itoa
 * @uno: nubr
 * @base: base
 * @flags: argument flags
 * Return: strg
 */
char *_trans_nubr(long int uno, int base, int flags)
{
	static char *array;
	char *ptr;
	static char buff[50];
	char sign = 0;
	unsigned long n = uno;

	if (!(flags & CONVERT_UNSIGNED) && uno < 0)
	{
		n = -uno;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _rm_cmts - func replaces 1st instance of '#' with '\0'
 * @buff: address of the str to modify
 * Return: 0 Always;
 */
void _rm_cmts(char *buff)
{
	int v;

	for (v = 0; buff[v] != '\0'; v++)
		if (buff[v] == '#' && (!v || buff[v - 1] == ' '))
		{
			buff[v] = '\0';
			break;
		}
}
