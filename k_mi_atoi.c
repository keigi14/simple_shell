#include "main.h"

/**
 * inter_act - returns true if shell's in inter_act mode
 * @info: structur address.
 * Return: 1 if inter_act mode, 0 ifnot.
 */
int inter_act(mi_info_on *info)
{
	return (isatty(STDIN_FILENO) && info->fle_reader <= 2);
}

/**
 * de_limiter - looks if char is a delimeter
 * @c: the char to be checked
 * @delim: thedelimeter strg
 * Return: 1 if true, 0 on false.
 */
int de_limiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * de_alpha - check for alphabetic char
 * @v: char to input
 * Return: 1 if v is alphabt, 0 ifnot.
 */

int de_alpha(int v)
{
	if ((v >= 'a' && v <= 'z') || (v >= 'A' && v <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * miatoi - converts a strg to an int.
 * @s: de str to be converted
 * Return: 0 if no nbrs in str, converted nubr ifnot
 */

int miatoi(char *s)
{
	int t, sign = 1, its_OP;
	int  flag = 0;
	unsigned int rezurt = 0;

	for (t = 0; s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sign *= -1;

		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			rezurt *= 10;
			rezurt += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		its_OP = -rezurt;
	else
		its_OP = rezurt;

	return (its_OP);
}
