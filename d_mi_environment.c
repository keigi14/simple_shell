#include "main.h"

/**
 * _mi_envi - prints the current environm.
 * @info: Struct containing potential arguments. Used to maintain
 * constant func prototype.
 * Return: 0 Always.
 */

int _mi_envi(mi_info_on *info)
{
	_pr_lst_str(info->playground);
	return (0);
}

/**
 * _gimi_env - give the value of anenvironmen variable
 * @infom: Struc containing potential arguments. Used to maintain
 * @name: suroundin var name
 * Return: de value
 */

char *_gimi_env(mi_info_on *infom, const char *name)
{
	mi_list_on *nod_e = infom->playground;
	char *g;

	while (nod_e)
	{
		g = _it_begins(nod_e->mi_stg, name);
		if (g && *g)
			return (g);
		nod_e = nod_e->next_nd;
	}
	return (NULL);
}

/**
 * _mi_made_env - Initializes new environment var,
 * or modify an existing one
 * @infom: Struct containing potential arguments.used to maintain
 * constant funct prototype.
 * Return: 0 Always.
 */

int _mi_made_env(mi_info_on *infom)
{
	if (infom->de_act != 3)
	{
		_c_lang_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_mi_putenv(infom, infom->de_av[1], infom->de_av[2]))
		return (0);
	return (1);
}

/**
 * _mi_unmade_env - Remove an environmnt variable
 * @info: Structur containing potential argument.Used to maintain
 * constant funct prototype.
 * Return: 0 Always.
 */

int _mi_unmade_env(mi_info_on *info)
{
	int v;

	if (info->de_act == 1)
	{
		_c_lang_puts("Too few arguements.\n");
		return (1);
	}
	for (v = 1; v <= info->de_act; v++)
		_mi_unputenv(info, info->de_av[v]);

	return (0);
}

/**
 * _fill_env_list - fills out envir linked list.
 * @info: Struct containing potential arguments.Used to maintain
 * constant funct prototype.
 * Return: 0 Always.
 */

int _fill_env_list(mi_info_on *info)
{
	size_t v;
	mi_list_on *node = NULL;

	for (v = 0; environ[v]; v++)
		_plus_node_end(&node, environ[v], 0);
	info->playground = node;
	return (0);
}
