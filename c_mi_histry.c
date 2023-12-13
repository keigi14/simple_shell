#include "main.h"

/**
 * _gimi_history_fl - gives the history file.
 * @info: parameter structure
 * Return: allocated strg containing history file
 */

char *_gimi_history_fl(mi_info_on *info)
{
	char *beef;
	char *dict;

	dict = _gimi_env(info, "HOME=");
	if (!dict)
		return (NULL);
	beef = malloc(sizeof(char) * (_string_lengt(dict) +
			      _string_lengt(HIST_FILE) + 2));
	if (!beef)
		return (NULL);
	beef[0] = 0;
	_strngs_cpy(beef, dict);
	_string_ct(beef, "/");
	_string_ct(beef, HIST_FILE);
	return (beef);
}

/**
 * _type_history - it creates thefile,or appends to an existing file.
 * @infom: the parameter structure.
 * Return: on success 1, else -1
 */

int _type_history(mi_info_on *infom)
{
	ssize_t fld;
	char *flnam = _gimi_history_fl(infom);
	mi_list_on *node = NULL;

	if (!flnam)
		return (-1);

	fld = open(flnam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(flnam);
	if (fld == -1)
		return (-1);
	for (node = infom->history; node; node = node->next_nd)
	{
		_puts_fld(node->mi_stg, fld);
		_put_fld('\n', fld);
	}
	_put_fld(BUF_FLUSH, fld);
	close(fld);
	return (1);
}

/**
 * _rd_de_history - read the history from file in it
 * @info: the parameter structure
 * Return: count_mi_hiss on success, 0 ifnot
 */
int _rd_de_history(mi_info_on *info)
{
	ssize_t fd, readlen, fsize = 0;
	int v, last = 0;
	int linecount = 0;
	struct stat st;
	char *buf = NULL, *flnam = _gimi_history_fl(info);

	if (!flnam)
		return (0);

	fd = open(flnam, O_RDONLY);
	free(flnam);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	readlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (v = 0; v < fsize; v++)
		if (buf[v] == '\n')
		{
			buf[v] = 0;
			_putup_history_list(info, buf + last, linecount++);
			last = v + 1;
		}
	if (last != v)
		_putup_history_list(info, buf + last, linecount++);
	free(buf);
	info->count_mi_hiss = linecount;
	while (info->count_mi_hiss-- >= HIST_MAX)
		_removw_node_on_index(&(info->history), 0);
	_renubr_history(info);
	return (info->count_mi_hiss);
}

/**
 * _putup_history_list - puts more entry to the history linked list.
 * @infom: Struct containing potential argumenfs. Used to maintain
 * @buf: buffer.
 * @linecount: the history linecount, count_mi_hiss
 * Return: 0 Always.
 */

int _putup_history_list(mi_info_on *infom, char *buf, int linecount)
{
	mi_list_on *mod_e = NULL;

	if (infom->history)
		mod_e = infom->history;
	_plus_node_end(&mod_e, buf, linecount);

	if (!infom->history)
		infom->history = mod_e;
	return (0);
}

/**
 * _renubr_history - renubers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Return: the new count_mi_hiss
 */

int _renubr_history(mi_info_on *info)
{
	mi_list_on *mod_e = info->history;
	int v = 0;

	while (mod_e)
	{
		mod_e->uno = v++;
		mod_e = mod_e->next_nd;
	}
	return (info->count_mi_hiss = v);
}
