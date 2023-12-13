#include "main.h"

/**
 * _mi_exit - exits the shell after done.
 * @infom: Struct containing potential argumnts.Used to maintain
 * constant func prototype.
 * Return: exit with a provide exit status.
 * (0) when info.de_av[0] != "exit"
 */

int _mi_exit(mi_info_on *infom)
{
	int exit_de_cek;

	if (infom->de_av[1]) /* If there is an exit argument */
	{
		exit_de_cek = de_erro_toi(infom->de_av[1]);
		if (exit_de_cek == -1)
		{
			infom->statue = 2;
			_pr_error(infom, "Illegal number: ");
			_c_lang_puts(infom->de_av[1]);
			_c_lang_putchar('\n');
			return (1);
		}
		infom->exit_wn_err = de_erro_toi(infom->de_av[1]);
		return (-2);
	}
	infom->exit_wn_err = -1;
	return (-2);
}

/**
 * _mi_cd - it change the current directry of the process
 * @info: Struct containing potential argumenfs.used to maintain
 * constant func prototype you wanna use.
 * Return: 0 Always.
 */

int _mi_cd(mi_info_on *info)
{
	char buffer[1024], *sing;
	char *m = getcwd(buffer, 1024);
	int chdir_ret;

	if (!m)
		_dis_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->de_av[1])
	{
		sing = _gimi_env(info, "HOME=");
		if (!sing)
			chdir_ret = /* TODO: what should this be? */
				chdir((sing = _gimi_env(info, "PWD=")) ? sing : "/");
		else
			chdir_ret = chdir(sing);
	}
	else if (_string_cmmp(info->de_av[1], "-") == 0)
	{
		if (!_gimi_env(info, "OLDPWD="))
		{
			_dis_puts(m);
			_o_puchar('\n');
			return (1);
		}
		_dis_puts(_gimi_env(info, "OLDPWD=")), _o_puchar('\n');
		chdir_ret = chdir((sing = _gimi_env(info, "OLDPWD=")) ? sing : "/");
	}
	else
		chdir_ret = chdir(info->de_av[1]);
	if (chdir_ret == -1)
	{
		_pr_error(info, "can't cd to ");
		_c_lang_puts(info->de_av[1]), _c_lang_putchar('\n');
	}
	else
	{
		_mi_putenv(info, "OLDPWD", _gimi_env(info, "PWD="));
		_mi_putenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _mi_help - its change the current directry of the process.
 * @info: Struct containing potential argumenfs.Used to maintain
 * constant func prototype.
 * Return: 0 Always.
 */
int _mi_help(mi_info_on *info)
{
	char **arg_array;

	arg_array = info->de_av;
	_dis_puts("help call works. Function not yet implemented \n");
	if (0)
		_dis_puts(*arg_array);/*jj*/
	return (0);
}
