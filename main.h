#ifndef _MAIN_H_


#define _MAIN_H_



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

/* for RW buff */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
/* 1 if*/
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct all_em_st - singly linked list
 * @uno: the nubr field
 * @mi_stg: a str
 * @next_nd: points to de next node.
 */

typedef struct all_em_st
{
	int uno;
	char *mi_stg;
	struct all_em_st *next_nd;
} mi_list_on;

/**
 * struct info_though - contains pseudo-arguments to pass into a func,
 * allowing uniform prototype for function ptr struct
 * @argmt: a string generated from getline containing arguements
 * @de_av:an array of strings generated from arg
 * @way: a string path for the current command
 * @de_act: the argument count
 * @row_countn: the error count
 * @exit_wn_err: the error code for exit()s
 * @flag_countsln: if on count this line of input
 * @p_fl_nm: the program filename
 * @playground: linked list local copy of environ
 * @suroundin: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @change_surr: on if environ was changed
 * @statue: the return status of the last exec'd cmnd
 * @buf_mi_ncmd: address of pointer to buf_mi_ncmd, on if chaining
 * @buf_mi_ncmd_typ: CMD_type ||, &&, ;
 * @fle_reader: the fd from which to read line input
 * @count_mi_hiss: the history line nubr count
 */
typedef struct info_though
{
	char *argmt;
	char **de_av;
	char *way;
	int de_act;
	unsigned int row_countn;
	int exit_wn_err;
	int flag_countsln;
	char *p_fl_nm;
	mi_list_on *playground;
	mi_list_on *history;
	mi_list_on *alias;
	char **suroundin;
	int change_surr;
	int statue;

	char **buf_mi_ncmd; /* pointer to cmd ; chain buffer, for memory mangement */
	int buf_mi_ncmd_typ; /* CMD_type ||, &&, ; */
	int fle_reader;
	int count_mi_hiss;
} mi_info_on;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/**
 * struct itsmibuiltin - have a builtin str and related func
 * @kind: the builtin command flag
 * @func: the func
 */
typedef struct itsmibuiltin
{
	char *kind;
	int (*func)(mi_info_on *);
} mi_builtin_tab;

/* */
int inter_act(mi_info_on *);
int de_limiter(char, char *);
int de_alpha(int);
int miatoi(char *);
/* */
int _mi_exit(mi_info_on *);
int _mi_cd(mi_info_on *);
int _mi_help(mi_info_on *);
/* */
int _mi_history(mi_info_on *);
int _mi_alias(mi_info_on *);
/* */
void _remove_inf(mi_info_on *);
void _intro_inf(mi_info_on *, char **);
void _free_inf(mi_info_on *, int);
/*  */
int _de_cmd(mi_info_on *, char *);
char *_dble_char(char *, int, int);
char *_look_path(mi_info_on *, char *, char *);
/*  */
int de_erro_toi(char *);
void _pr_error(mi_info_on *, char *);
int _pr_dec(int, int);
char *_trans_nubr(long int, int, int);
void _rm_cmts(char *);
/*  */
char *_st_cp(char *, char *, int);
char *_stn_ct(char *, char *, int);
char *_stn_chara(char *, char);
/**/
char **_gimi_environm(mi_info_on *);
int _mi_unputenv(mi_info_on *, char *);
int _mi_putenv(mi_info_on *, char *, char *);


/* */
char *_gimi_env(mi_info_on *, const char *);
int _mi_envi(mi_info_on *);
int _mi_made_env(mi_info_on *);
int _mi_unmade_env(mi_info_on *);
int _fill_env_list(mi_info_on *);
/*  */
ssize_t _de_imput_buf(mi_info_on *, char **, size_t *);
ssize_t _gv_input_to(mi_info_on *);
ssize_t _mi_readn_fuf(mi_info_on *, char *, size_t *);
int _de_get_line(mi_info_on *, char **, size_t *);
void _si_handler(int);
/* */
char *_gimi_history_fl(mi_info_on *info);
int _type_history(mi_info_on *info);
int _rd_de_history(mi_info_on *info);
int _putup_history_list(mi_info_on *info, char *buf, int linecount);
int _renubr_history(mi_info_on *info);
/* */
mi_list_on *_plus_more_node(mi_list_on **, const char *, int);
mi_list_on *_plus_node_end(mi_list_on **, const char *, int);
size_t _pr_lst_str(const mi_list_on *);
int _removw_node_on_index(mi_list_on **, unsigned int);
void _free_de_lst(mi_list_on **);
/* */
size_t _lsts_length(const mi_list_on *);
char **_lsts_tostrs(mi_list_on *);
size_t _pr_lists_(const mi_list_on *);
mi_list_on *_de_node_begin(mi_list_on *, char *, char);
ssize_t _give_nd_index(mi_list_on *, mi_list_on *);
/*  */
int _get_free(void **);
/*  */
void _c_lang_puts(char *);
int _c_lang_putchar(char);
int _put_fld(char c, int fd);
int _puts_fld(char *str, int fd);
/* */
char *_memo_puton(char *, char, unsigned int);
void _fr_free(char **);
void *_mi_realloc(void *, unsigned int, unsigned int);
/*  */
int h_shy(mi_info_on *, char **);
int _look_builtin(mi_info_on *);
void _gimi_cmmd(mi_info_on *);
void _fork_cmmd(mi_info_on *);


/**/
int _string_lengt(char *);
int _string_cmmp(char *, char *);
char *_it_begins(const char *, const char *);
char *_string_ct(char *, char *);
/* */
char *_strngs_cpy(char *, char *);
char *_string_dupo(const char *);
void _dis_puts(char *);
int _o_puchar(char);
/* */
char **_string_tower(char *, char *);
char **_string_tower2(char *, char);
/* */
int ze_chainin(mi_info_on *, char *, size_t *);
void looks_chain(mi_info_on *, char *, size_t *, size_t, size_t);
int n_alias_up(mi_info_on *);
int _clean_vars(mi_info_on *);
int _clear_strg(char **, char *);

/* */
int _loop_hsy(char **);

#endif
