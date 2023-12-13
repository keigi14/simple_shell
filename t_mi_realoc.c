#include "main.h"

/**
 * _memo_puton - fills de memory with a constant byte
 * @m: the ptr to the memory area.
 * @v: byte to fill *s with
 * @p: the numb of bytes to be filled
 * Return: (s) a pter to the memory area s
 */
char *_memo_puton(char *m, char v, unsigned int p)
{
	unsigned int t;

	for (t = 0; t < p; t++)
		m[t] = v;
	return (m);
}

/**
 * _fr_free - frees the str of strs
 * @pk: str of strgs
 */
void _fr_free(char **pk)
{
	char **v = pk;

	if (!pk)
		return;
	while (*pk)
		free(*pk++);
	free(v);
}

/**
 * _mi_realloc - itreallocate a block of memory to.
 * @ptr: ptr to previous dallocated codeblock
 * @size_o: sizein bytes of previous block
 * @size_n: sizein byte of new block
 * Return: ptr to da ol'block nameen.
 */
void *_mi_realloc(void *ptr, unsigned int size_o, unsigned int size_n)
{
	char *o;

	if (!ptr)
		return (malloc(size_n));
	if (!size_n)
		return (free(ptr), NULL);
	if (size_n == size_o)
		return (ptr);

	o = malloc(size_n);
	if (!o)
		return (NULL);

	size_o = size_o < size_n ? size_o : size_n;
	while (size_o--)
		o[size_o] = ((char *)ptr)[size_o];
	free(ptr);
	return (o);
}
