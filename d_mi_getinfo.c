#include "main.h"

/**
 * _remove_inf - initializes mi_info_on structure
 * @info: structure address
 */

void _remove_inf(mi_info_on *info)
{
	info->argmt = NULL;
	info->de_av = NULL;
	info->way = NULL;
	info->de_act = 0;
}

/**
 * _intro_inf - initializing mi_info_on structure.
 * @info: structure address
 * @av: argumnt vector
 */

void _intro_inf(mi_info_on *info, char **av)
{
	int v = 0;

	info->p_fl_nm = av[0];
	if (info->argmt)
	{
		info->de_av = _string_tower(info->argmt, " \t");
		if (!info->de_av)
		{
			info->de_av = malloc(sizeof(char *) * 2);
			if (info->de_av)
			{
				info->de_av[0] = _string_dupo(info->argmt);
				info->de_av[1] = NULL;
			}
		}
		for (v = 0; info->de_av && info->de_av[v]; v++)
			;
		info->de_act = v;

		n_alias_up(info);
		_clean_vars(info);
	}
}

/**
 * _free_inf - frees mi_info_on struct fields
 * @info: structure address
 * @all: true if freing all fields
 */

void _free_inf(mi_info_on *info, int all)
{
	_fr_free(info->de_av);
	info->de_av = NULL;
	info->way = NULL;
	if (all)
	{
		if (!info->buf_mi_ncmd)
			free(info->argmt);
		if (info->playground)
			_free_de_lst(&(info->playground));
		if (info->history)
			_free_de_lst(&(info->history));
		if (info->alias)
			_free_de_lst(&(info->alias));
		_fr_free(info->suroundin);
			info->suroundin = NULL;
		_get_free((void **)info->buf_mi_ncmd);
		if (info->fle_reader > 2)
			close(info->fle_reader);
		_o_puchar(BUF_FLUSH);
	}
}
