#include "main.h"

/**
 * _get_free - this frees aptr and NULL the address it belngs
 * @piter: address of the ptr to free.
 * Return: 1 if its freed, ifnot 0.
 */
int _get_free(void **piter)
{
	if (piter && *piter)
	{
		free(*piter);
		*piter = NULL;
		return (1);
	}
	return (0);
}
