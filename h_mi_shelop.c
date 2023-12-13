#include "main.h"

/**
 * h_shy - its the main shell loop
 * @infom: the parameter and the return info struct
 * @av: the argmnt vector from main()
 * Return: 0 as success, 1 as error,or error code
 */
int h_shy(mi_info_on *infom, char **av)
{
	int builtin_ret = 0;
	ssize_t q = 0;

	while (q != -1 && builtin_ret != -2)
	{
		_remove_inf(infom);
		if (inter_act(infom))
			_c_lang_puts("$ ");
		_c_lang_putchar(BUF_FLUSH);
		q = _gv_input_to(infom);
		if (q != -1)
		{
			_intro_inf(infom, av);
			builtin_ret = _look_builtin(infom);
			if (builtin_ret == -1)
				_gimi_cmmd(infom);
		}
		else if (inter_act(infom))
			_o_puchar('\n');
		_free_inf(infom, 0);
	}
	_type_history(infom);
	_free_inf(infom, 1);
	if (!inter_act(infom) && infom->statue)
		exit(infom->statue);
	if (builtin_ret == -2)
	{
		if (infom->exit_wn_err == -1)
			exit(infom->statue);
		exit(infom->exit_wn_err);
	}
	return (builtin_ret);
}

/**
 * _look_builtin - looks for builtin command
 * @infom: the parameter and return info struct
 * Return: -1 if builtin  is not found
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 * 0 if builtin executed successfully
 */
int _look_builtin(mi_info_on *infom)
{
	int i, built_in_ret = -1;
	mi_builtin_tab builtintbl[] = {
		{"exit", _mi_exit},
		{"env", _mi_envi},
		{"help", _mi_help},
		{"history", _mi_history},
		{"_mi_putenv", _mi_made_env},
		{"_mi_unputenv", _mi_unmade_env},
		{"cd", _mi_cd},
		{"alias", _mi_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].kind; i++)
		if (_string_cmmp(infom->de_av[0], builtintbl[i].kind) == 0)
		{
			infom->row_countn++;
			built_in_ret = builtintbl[i].func(infom);
			break;
		}
	return (built_in_ret);
}

/**
 * _gimi_cmmd - find a comand in PATH
 * @infom: the parameter & return info struct
 * Return: void as it is
 */
void _gimi_cmmd(mi_info_on *infom)
{
	int t;
	char *way = NULL;
	int k;

	infom->way = infom->de_av[0];
	if (infom->flag_countsln == 1)
	{
		infom->row_countn++;
		infom->flag_countsln = 0;
	}
	for (t = 0, k = 0; infom->argmt[t]; t++)
		if (!de_limiter(infom->argmt[t], " \t\n"))
			k++;
	if (!k)
		return;

	way = _look_path(infom, _gimi_env(infom, "PATH="), infom->de_av[0]);
	if (way)
	{
		infom->way = way;
		_fork_cmmd(infom);
	}
	else
	{
		if ((inter_act(infom) || _gimi_env(infom, "PATH=")
					|| infom->de_av[0][0] == '/') && _de_cmd(infom, infom->de_av[0]))
			_fork_cmmd(infom);
		else if (*(infom->argmt) != '\n')
		{
			infom->statue = 127;
			_pr_error(infom, "not found\n");
		}
	}
}

/**
 * _fork_cmmd - fork an exec thread to run cmd command
 * @infom: parameter & return info struct
 * Return: void not a value
 */
void _fork_cmmd(mi_info_on *infom)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infom->way, infom->de_av, _gimi_environm(infom)) == -1)
		{
			_free_inf(infom, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infom->statue));
		if (WIFEXITED(infom->statue))
		{
			infom->statue = WEXITSTATUS(infom->statue);
			if (infom->statue == 126)
				_pr_error(infom, "Permission denied\n");
		}
	}
}
