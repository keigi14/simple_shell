#include "main.h"

/**
 * _string_lengt - return the how long a str is
 * @v: a str whose length to check
 * Return: int length of str.
 */
int _string_lengt(char *v)
{
	int k = 0;

	if (!v)
		return (0);

	while (*v++)
		k++;
	return (k);
}

/**
 * _string_cmmp - perform lexicogarphic comparison of two strs.
 * @v1: the 1st strg
 * @v2: the 2nd strg
 * Return: negative if v1 < v2, positive if v1 > v2,or zero if v1 == v2.
 */
int _string_cmmp(char *v1, char *v2)
{
	while (*v1 && *v2)
	{
		if (*v1 != *v2)
			return (*v1 - *v2);
		v1++;
		v2++;
	}
	if (*v1 == *v2)
		return (0);
	else
		return (*v1 < *v2 ? -1 : 1);
}

/**
 *_it_begins - checks if needle starts with tnystark
 * @tnystark: str to search
 * @sword: the substr to find
 * Return: address of next character of tnystark or NULL
 */
char *_it_begins(const char *tnystark, const char *sword)
{
	while (*sword)
		if (*sword++ != *tnystark++)
			return (NULL);
	return ((char *)tnystark);
}

/**
 * _string_ct - concatenates two strs
 * @destin: the destination buffer
 * @src: the source buffer
 * Return: ptr to destination buffer
 */
char *_string_ct(char *destin, char *src)
{
	char *ret = destin;

	while (*destin)
		destin++;
	while (*src)
		*destin++ = *src++;
	*destin = *src;
	return (ret);
}
