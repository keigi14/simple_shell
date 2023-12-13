#include "main.h"

/**
 * _mi_history - displas  history list,one cmd by line, preceded
 * with line nubrs, beginning at 0.
 * @info: Structur containing potential arguments.Used to maintain
 * constant func prototype.
 * Return: 0 Always.
 */

int _mi_history(mi_info_on *info)
{
	_pr_lists_(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to str
 * @info: parameter structure
 * @mi_stg: the str alias
 * Return: 0 Always on success,1 on error
 */
int unset_alias(mi_info_on *info, char *mi_stg)
{
	int gimi;
	char *v;
	char c;

	v = _stn_chara(mi_stg, '=');
	if (!v)
		return (1);
	c = *v;
	*v = 0;
	gimi = _removw_node_on_index(&(info->alias),
			_give_nd_index(info->alias, _de_node_begin(info->alias, mi_stg, -1)));
	*v = c;
	return (gimi);
}

/**
 * set_alias - sets alias to mi_stg
 * @info: parameter structure
 * @mi_stg: the strg alias
 * Return: 0 Always on success,1 on error
 */
int set_alias(mi_info_on *info, char *mi_stg)
{
	char *v;

	v = _stn_chara(mi_stg, '=');
	if (!v)
		return (1);
	if (!*++v)
		return (unset_alias(info, mi_stg));

	unset_alias(info, mi_stg);
	return (_plus_node_end(&(info->alias), mi_stg, 0) == NULL);
}

/**
 * print_alias - print an alias str
 * @node: the alias node
 * Return: 0 Always on success, 1 on error
 */

int print_alias(mi_list_on *node)
{
	char *v = NULL;
	char *a = NULL;

	if (node)
	{
		v = _stn_chara(node->mi_stg, '=');
		for (a = node->mi_stg; a <= v; a++)
			_o_puchar(*a);
		_o_puchar('\'');
		_dis_puts(v + 1);
		_dis_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _mi_alias - it mimics an alia builtin (man alias)
 * @info: Struct containing potential argumenfs. Used to maintain
 * constant funct prototype.
 * Return: 0 Always.
 */
int _mi_alias(mi_info_on *info)
{
	int k = 0;
	char *p = NULL;

	mi_list_on *node = NULL;

	if (info->de_act == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next_nd;
		}
		return (0);
	}
	for (k = 1; info->de_av[k]; k++)
	{
		p = _stn_chara(info->de_av[k], '=');
		if (p)
			set_alias(info, info->de_av[k]);
		else
			print_alias(_de_node_begin(info->alias, info->de_av[k], '='));
	}

	return (0);
}
