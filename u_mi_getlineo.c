#include "main.h"

/**
 * _de_imput_buf - the buffers chained commands.
 * @infom: parameter structure to use.
 * @len: location of len var
 * @buf: location of buffer.
 * Return: bytes that have been read
 */

ssize_t _de_imput_buf(mi_info_on *infom, char **buf, size_t *len)
{
	size_t len_p = 0;
	ssize_t r = 0;

	if (!*len) /* if nothing's left in the buffer, fill it */
	{
		/*_get_free((void **)info->buf_mi_ncmd);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _si_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _de_get_line(infom, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infom->flag_countsln = 1;
			_rm_cmts(*buf);
			_putup_history_list(infom, *buf, infom->count_mi_hiss++);
			/* if (_stn_chara(*buf, ';')) is this a command chain? */
			{
				*len = r;
				infom->buf_mi_ncmd = buf;
			}
		}
	}
	return (r);
}

/**
 * _gv_input_to - provides a line minus the newline.
 * @info: parameter structur
 * Return: bytes read
 */

ssize_t _gv_input_to(mi_info_on *info)
{
	static char *buf; /* the ';' command chain buffer */
	ssize_t q = 0;
	static size_t v, j, len;
	char **buf_p = &(info->argmt), *p;

	_o_puchar(BUF_FLUSH);
	q = _de_imput_buf(info, &buf, &len);
	if (q == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = v; /* init new iterator to current buf position */
		p = buf + v; /* get pointer for return */

		looks_chain(info, buf, &j, v, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (ze_chainin(info, buf, &j))
				break;
			j++;
		}

		v = j + 1; /* increment past nulled ';'' */
		if (v >= len) /* reached end of buffer? */
		{
			v = len = 0; /* reset position and length */
			info->buf_mi_ncmd_typ = CMD_NORM;
		}

		*buf_p = p; /* pass back ptr to current comand position */
		return (_string_lengt(p)); /* return length of current comand */
	}

	*buf_p = buf; /* else not a chain,pass back buffer from _de_get_line*/
	return (q); /* return length of buffer from _de_get_line() */
}

/**
 * _mi_readn_fuf - reads a buffer
 * @info: parameter structure
 * @buf: buffer
 * @i: size
 * Return: r
 */

ssize_t _mi_readn_fuf(mi_info_on *info, char *buf, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(info->fle_reader, buf, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}

/**
 * _de_get_line - getz the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of ptr to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */

int _de_get_line(mi_info_on *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	ssize_t r = 0, s = 0;
	size_t k;
	char *p = NULL, *fresh_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (t == len)
		t = len = 0;

	r = _mi_readn_fuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _stn_chara(buf + t, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	fresh_p = _mi_realloc(p, s, s ? s + k : k + 1);
	if (!fresh_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_stn_ct(fresh_p, buf + t, k - t);
	else
		_st_cp(fresh_p, buf + t, k - t + 1);

	s += k - t;
	t = k;
	p = fresh_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _si_handler - blocks ctrl-C
 * @nubr_sig: the signal nubr.
 * Return: void
 */

void _si_handler(__attribute__((unused))int nubr_sig)
{
	_dis_puts("\n");
	_dis_puts("$ ");
	_o_puchar(BUF_FLUSH);
}
