#include "main.h"

/**
 * main - de entry point
 * @ac: an arg count
 * @av: an arg vector
 * Return: on success 0, 1 onerror
 */

int main(int ac, char **av)
{
	mi_info_on info[] = { INFO_INIT };
	int flde = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (flde)
			: "r" (flde));

	if (ac == 2)
	{
		flde = open(av[1], O_RDONLY);
		if (flde == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_c_lang_puts(av[0]);
				_c_lang_puts(": 0: Can't open ");
				_c_lang_puts(av[1]);
				_c_lang_putchar('\n');
				_c_lang_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fle_reader = flde;
	}
	_fill_env_list(info);
	_rd_de_history(info);
	h_shy(info, av);
	return (EXIT_SUCCESS);
}
