#include "main.h"

/**
 * _plus_more_node - add a node,to the start of list.
 * @head: address of ptr to de head node.
 * @mi_stg: the string field of node.
 * @uno: node index that's used in history.
 * Return: de size of list
 */

mi_list_on *_plus_more_node(mi_list_on **head, const char *mi_stg, int uno)
{
	mi_list_on *latest_hd;

	if (!head)
		return (NULL);
	latest_hd = malloc(sizeof(mi_list_on));
	if (!latest_hd)
		return (NULL);
	_memo_puton((void *)latest_hd, 0, sizeof(mi_list_on));
	latest_hd->uno = uno;
	if (mi_stg)
	{
		latest_hd->mi_stg = _string_dupo(mi_stg);
		if (!latest_hd->mi_stg)
		{
			free(latest_hd);
			return (NULL);
		}
	}
	latest_hd->next_nd = *head;
	*head = latest_hd;
	return (latest_hd);
}

/**
 * _plus_node_end - adds a node at theend of list
 * @head: addresses of ptr to head node.
 * @mi_stg: string field of node.
 * @uno: de node index used in history.
 * Return: de size of the list
 */

mi_list_on *_plus_node_end(mi_list_on **head, const char *mi_stg, int uno)
{
	mi_list_on *latest_nod, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	 latest_nod = malloc(sizeof(mi_list_on));
	if (!latest_nod)
		return (NULL);
	_memo_puton((void *)latest_nod, 0, sizeof(mi_list_on));
	latest_nod->uno = uno;
	if (mi_stg)
	{
		latest_nod->mi_stg = _string_dupo(mi_stg);
		if (!latest_nod->mi_stg)
		{
			free(latest_nod);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next_nd)
			nde = nde->next_nd;
		nde->next_nd = latest_nod;
	}
	else
		*head = latest_nod;
	return (latest_nod);
}

/**
 * _pr_lst_str - prints only the str element of mi_list_on .
 * @h: ptr to the 1st node.
 * Return: de size of list.
 */

size_t _pr_lst_str(const mi_list_on *h)
{
	size_t v = 0;

	while (h)
	{
		_dis_puts(h->mi_stg ? h->mi_stg : "(nil)");
		_dis_puts("\n");
		h = h->next_nd;
		v++;
	}
	return (v);
}

/**
 * _removw_node_on_index - removes node at a given index.
 * @head: address of ptr to 1st node.
 * @index: index of node to remove
 * Return: if success 1, 0 on failure
 */

int _removw_node_on_index(mi_list_on **head, unsigned int index)
{
	mi_list_on *nde, *passed_nod;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nde = *head;
		*head = (*head)->next_nd;
		free(nde->mi_stg);
		free(nde);
		return (1);
	}
	nde = *head;
	while (nde)
	{
		if (i == index)
		{
			passed_nod->next_nd = nde->next_nd;
			free(nde->mi_stg);
			free(nde);
			return (1);
		}
		i++;
		passed_nod = nde;
		nde = nde->next_nd;
	}
	return (0);
}

/**
 * _free_de_lst - frees all the nodes of a list.
 * @head_ptr: address of ptr to head node.
 * Return: its void
 */

void _free_de_lst(mi_list_on **head_ptr)
{
	mi_list_on *nd, *next_nde, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nd = head;
	while (nd)
	{
		next_nde = nd->next_nd;
		free(nd->mi_stg);
		free(nd);
		nd = next_nde;
	}
	*head_ptr = NULL;
}
