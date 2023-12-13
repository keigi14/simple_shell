#include "main.h"

/**
 * _de_cmd - decides if file is an executable comand
 * @infom: info structure.
 * @way: the path to the fl
 * Return: 1 if true, 0 ifnot
 */
int _de_cmd(mi_info_on *infom, char *way)
{
	struct stat st;

	(void)infom;
	if (!way || stat(way, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dble_char - duplicates or doubles chars
 * @waystr: the PATH str
 * @start: beginning index
 * @stop: ending index
 * Return: ptr to new buffer
 */
char *_dble_char(char *waystr, int start, int stop)
{
	static char buf[1024];
	int z = 0;
	int v = 0;

	for (v = 0, z = start; z < stop; z++)
		if (waystr[z] != ':')
			buf[v++] = waystr[z];
	buf[v] = 0;
	return (buf);
}

/**
 * _look_path - finds this command in path as str
 * @info: info struct
 * @waystr: PATH str
 * @cmd: the comand to find
 * Return: complete path of comand found or NULL
 */
char *_look_path(mi_info_on *info, char *waystr, char *cmd)
{
	char *way;
	int t = 0;
	int curr_pos = 0;

	if (!waystr)
		return (NULL);
	if ((_string_lengt(cmd) > 2) && _it_begins(cmd, "./"))
	{
		if (_de_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!waystr[t] || waystr[t] == ':')
		{
			way = _dble_char(waystr, curr_pos, t);
			if (!*way)
				_string_ct(way, cmd);
			else
			{
				_string_ct(way, "/");
				_string_ct(way, cmd);
			}
			if (_de_cmd(info, way))
				return (way);
			if (!waystr[t])
				break;
			curr_pos = t;
		}
		t++;
	}
	return (NULL);
}
