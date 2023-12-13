#include "main.h"

/**
 *  _lsts_length- decides length of the linked list.
 * @h: ptr to 1st node.
 * Return: size of the list
 */

size_t _lsts_length(const mi_list_on *h)
{
	size_t v = 0;

	while (h)
	{
		h = h->next_nd;
		v++;
	}
	return (v);
}

/**
 * _lsts_tostrs - returns an array of strgz of list->mi_stg.
 * @head: ptr to the 1st node.
 * Return: array of strgs
 */

char **_lsts_tostrs(mi_list_on *head)
{
	mi_list_on *nde = head;
	size_t i = _lsts_length(head), j;
	char **mi_stgs;
	char *mi_stg;

	if (!head || !i)
		return (NULL);
	mi_stgs = malloc(sizeof(char *) * (i + 1));
	if (!mi_stgs)
		return (NULL);
	for (i = 0; nde; nde = nde->next_nd, i++)
	{
		mi_stg = malloc(_string_lengt(nde->mi_stg) + 1);
		if (!mi_stg)
		{
			for (j = 0; j < i; j++)
				free(mi_stgs[j]);
			free(mi_stgs);
			return (NULL);
		}

		mi_stg = _strngs_cpy(mi_stg, nde->mi_stg);
		mi_stgs[i] = mi_stg;
	}
	mi_stgs[i] = NULL;
	return (mi_stgs);
}


/**
 * _pr_lists_ - it prints all elements of de mi_list_on linked list
 * @h: ptr to 1st node
 * Return: size of list
 */

size_t _pr_lists_(const mi_list_on *h)
{
	size_t v = 0;

	while (h)
	{
		_dis_puts(_trans_nubr(h->uno, 10, 0));
		_o_puchar(':');
		_o_puchar(' ');
		_dis_puts(h->mi_stg ? h->mi_stg : "(nil)");
		_dis_puts("\n");
		h = h->next_nd;
		v++;
	}
	return (v);
}

/**
 * _de_node_begin - returns de node whose str begins with prefix
 * @node: ptr to the list head
 * @prefx: strg to match with.
 * @c: the next char after prefix to match.
 * Return: match the node or null.
 */

mi_list_on *_de_node_begin(mi_list_on *node, char *prefx, char c)
{
	char *v = NULL;

	while (node)
	{
		v = _it_begins(node->mi_stg, prefx);
		if (v && ((c == -1) || (*v == c)))
			return (node);
		node = node->next_nd;
	}
	return (NULL);
}

/**
 * _give_nd_index - gives the index of de node
 * @head: ptr to list head
 * @nod: ptr to the node
 * Return: index of node or -1.
 */

ssize_t _give_nd_index(mi_list_on *head, mi_list_on *nod)
{
	size_t v = 0;

	while (head)
	{
		if (head == nod)
			return (v);
		head = head->next_nd;
		v++;
	}
	return (-1);
}
