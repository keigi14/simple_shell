#include "main.h"

/**
 * **_string_tower - split str into single words.Repeat delimiter are ignored
 * @mi_stg: input str
 * @d: the delimeter str
 * Return: a ptr to array of str,or NULL on failure
 */

char **_string_tower(char *mi_stg, char *d)
{
	int t, l, b;
	char **v;
	int m, nubr_word = 0;

	if (mi_stg == NULL || mi_stg[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (t = 0; mi_stg[t] != '\0'; t++)
		if (!de_limiter(mi_stg[t], d) &&
			(de_limiter(mi_stg[t + 1], d) || !mi_stg[t + 1]))
			nubr_word++;

	if (nubr_word == 0)
		return (NULL);
	v = malloc((1 + nubr_word) * sizeof(char *));
	if (!v)
		return (NULL);
	for (t = 0, l = 0; l < nubr_word; l++)
	{
		while (de_limiter(mi_stg[t], d))
			t++;
		b = 0;
		while (!de_limiter(mi_stg[t + b], d) && mi_stg[t + b])
			b++;
		v[l] = malloc((b + 1) * sizeof(char));
		if (!v[l])
		{
			for (b = 0; b < l; b++)
				free(v[b]);
			free(v);
			return (NULL);
		}
		for (m = 0; m < b; m++)
			v[l][m] = mi_stg[t++];
		v[l][m] = 0;
	}
	v[l] = NULL;
	return (v);
}

/**
 * **_string_tower2 - divides a str into words
 * @mi_stg: an input str
 * @d: a delimeter
 * Return: a ptr to array of strgs,or NULL on failure
 */
char **_string_tower2(char *mi_stg, char d)
{
	int t, l, b;
	int m, nubr_word = 0;
	char **s;

	if (mi_stg == NULL || mi_stg[0] == 0)
		return (NULL);
	for (t = 0; mi_stg[t] != '\0'; t++)
		if ((mi_stg[t] != d && mi_stg[t + 1] == d) ||
				(mi_stg[t] != d && !mi_stg[t + 1]) || mi_stg[t + 1] == d)
			nubr_word++;
	if (nubr_word == 0)
		return (NULL);
	s = malloc((1 + nubr_word) * sizeof(char *));
	if (!s)
		return (NULL);
	for (t = 0, l = 0; l < nubr_word; l++)
	{
		while (mi_stg[t] == d && mi_stg[t] != d)
			t++;
		b = 0;
		while (mi_stg[t + b] != d && mi_stg[t + b] && mi_stg[t + b] != d)
			b++;
		s[l] = malloc((b + 1) * sizeof(char));
		if (!s[l])
		{
			for (b = 0; b < l; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < b; m++)
			s[l][m] = mi_stg[t++];
		s[l][m] = 0;
	}
	s[l] = NULL;
	return (s);
}
