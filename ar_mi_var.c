#include "main.h"

/**
 * ze_chainin - it tests if current char in bufer's a chain delimeter
 * @infom: de parameter structure
 * @buf: the charac buffer
 * @x: address of current position in buff.as it is.
 * Return: if chain delimeter a 1, 10.
 */

int ze_chainin(mi_info_on *infom, char *buf, size_t *x)
{
	size_t v = *x;

	if (buf[v] == '|' && buf[v + 1] == '|')
	{
		buf[v] = 0;
		v++;
		infom->buf_mi_ncmd_typ = CMD_OR;
	}
	else if (buf[v] == '&' && buf[v + 1] == '&')
	{
		buf[v] = 0;
		v++;
		infom->buf_mi_ncmd_typ = CMD_AND;
	}
	else if (buf[v] == ';') /* found end of this command */
	{
		buf[v] = 0; /* replace semicolon with null */
		infom->buf_mi_ncmd_typ = CMD_CHAIN;
	}
	else
		return (0);
	*x = v;
	return (1);
}

/**
 * looks_chain - checks to continue chains based by delast status
 * @infom: that parameter structur
 * @buff: the charactr buffer
 * @i: beginning position in buf
 * @p: location of current position in buffer
 * @len: len of buf
 * Return: Void.
 */
void looks_chain(mi_info_on *infom, char *buff,
		size_t *p, size_t i, size_t len)
{
	size_t g = *p;

	if (infom->buf_mi_ncmd_typ == CMD_AND)
	{
		if (infom->statue)
		{
			buff[i] = 0;
			g = len;
		}
	}
	if (infom->buf_mi_ncmd_typ == CMD_OR)
	{
		if (!infom->statue)
		{
			buff[i] = 0;
			g = len;
		}
	}

	*p = g;
}

/**
 * n_alias_up - replaces an aliases inthe tokenized str
 * @infom: de parameter structure.
 * Return: 1 if replaced, 0 ifnot
 */

int n_alias_up(mi_info_on *infom)
{
	mi_list_on *nde;
	char *p;
	int v;

	for (v = 0; v < 10; v++)
	{
		nde = _de_node_begin(infom->alias, infom->de_av[0], '=');
		if (!nde)
			return (0);
		free(infom->de_av[0]);
		p = _stn_chara(nde->mi_stg, '=');
		if (!p)
			return (0);
		p = _string_dupo(p + 1);
		if (!p)
			return (0);
		infom->de_av[0] = p;
	}
	return (1);
}

/**
 * _clean_vars - replace vars in the tokenized str
 * @info: the parameter structure
 * Return: if replaced 1, 0 ifnot
 */
int _clean_vars(mi_info_on *info)
{
	mi_list_on *nod;
	int v = 0;

	for (v = 0; info->de_av[v]; v++)
	{
		if (info->de_av[v][0] != '$' || !info->de_av[v][1])
			continue;

		if (!_string_cmmp(info->de_av[v], "$?"))
		{
			_clear_strg(&(info->de_av[v]),
					_string_dupo(_trans_nubr(info->statue, 10, 0)));
			continue;
		}
		if (!_string_cmmp(info->de_av[v], "$$"))
		{
			_clear_strg(&(info->de_av[v]),
					_string_dupo(_trans_nubr(getpid(), 10, 0)));
			continue;
		}
		nod = _de_node_begin(info->playground, &info->de_av[v][1], '=');
		if (nod)
		{
			_clear_strg(&(info->de_av[v]),
					_string_dupo(_stn_chara(nod->mi_stg, '=') + 1));
			continue;
		}
		_clear_strg(&info->de_av[v], _string_dupo(""));

	}
	return (0);
}

/**
 * _clear_strg - it replaces str.
 * @mzh: address of old strg
 * @ne: the new strg
 * Return: 1 if replaced, 0 ifnot
 */

int _clear_strg(char **mzh, char *ne)
{
	free(*mzh);
	*mzh = ne;
	return (1);
}
