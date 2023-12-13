#include "main.h"

/**
 **_st_cp - copies a str
 *@dest: the destination str to be copied to
 *@src: the source str
 *@n: the amount of chars to be copied
 *Return: a concatenated str
 */
char *_st_cp(char *dest, char *src, int n)
{
	int m;
	int j;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		j = m;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_stn_ct - concatenates two strs
 *@dest: the 1st str
 *@src: the 2nd str
 *@n: the amount of bytes to be maximally used in str
 *Return: the concatenated str
 */
char *_stn_ct(char *dest, char *src, int n)
{
	int v, j;
	char *s = dest;

	v = 0;
	j = 0;
	while (dest[v] != '\0')
		v++;
	while (src[j] != '\0' && j < n)
	{
		dest[v] = src[j];
		v++;
		j++;
	}
	if (j < n)
		dest[v] = '\0';
	return (s);
}

/**
 **_stn_chara - locates a char in a str
 *@s: the str to be parsed
 *@c: the char you wanna look for
 *Return: (s) a ptr to the memory area s
 */
char *_stn_chara(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
