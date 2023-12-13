#include "main.h"

/**
 * _gimi_environm - returns str array copy of our environmnt
 * @infom: Struct containing potential arguments. Used to maintain
 * constant funct prototype.
 * Return: 0 Always.
 */

char **_gimi_environm(mi_info_on *infom)
{
	if (!infom->suroundin || infom->change_surr)
	{
		infom->suroundin = _lsts_tostrs(infom->playground);
		infom->change_surr = 0;
	}

	return (infom->suroundin);
}

/**
 * _mi_unputenv - it deletes an environmet variable.
 * @info: Structure containing potential argumenfs.Used to maintain
 * constant funct prototype.
 * Return: on delete 1, 0 ifnot.
 * @var: the str suroundin var property.
 */

int _mi_unputenv(mi_info_on *info, char *var)
{
	mi_list_on *node = info->playground;
	char *p;
	size_t v = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _it_begins(node->mi_stg, var);
		if (p && *p == '=')
		{
			info->change_surr = _removw_node_on_index(&(info->playground), v);
			v = 0;
			node = info->playground;
			continue;
		}
		node = node->next_nd;
		v++;
	}
	return (info->change_surr);
}

/**
 * _mi_putenv- Initialize new suroundin variable,
 * or modify the existing one
 * @info: Struct containing potential arguments. Used to maintain
 * constant func prototype.
 * @var: the strg envin var property
 * @value: the strg envin var value
 *  Return: 0 Always.
 */

int _mi_putenv(mi_info_on *info, char *var, char *value)
{
	char *buf = NULL;
	mi_list_on *node;
	char *v;

	if (!var || !value)
		return (0);

	buf = malloc(_string_lengt(var) + _string_lengt(value) + 2);
	if (!buf)
		return (1);
	_strngs_cpy(buf, var);
	_string_ct(buf, "=");
	_string_ct(buf, value);
	node = info->playground;
	while (node)
	{
		v = _it_begins(node->mi_stg, var);
		if (v && *v == '=')
		{
			free(node->mi_stg);
			node->mi_stg = buf;
			info->change_surr = 1;
			return (0);
		}
		node = node->next_nd;
	}
	_plus_node_end(&(info->playground), buf, 0);
	free(buf);
	info->change_surr = 1;
	return (0);
}
