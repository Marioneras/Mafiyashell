/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:33 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/27 10:15:45 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// shakkuyakuu

#ifndef MINISHELL_H
#define MINISHELL_H

#define _GNU_SOURCE
#include "libft.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

#define PATH_MAX 4096

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

extern volatile sig_atomic_t g_signal;

typedef struct s_token
{
	char *name;
	int type;
	struct s_token *next;
	struct s_token *previous;
} t_token;

typedef enum e_type
{
	EMPTY,
	CMD,
	ARGUMENT,
	PIPE,
	TRUNC,
	INPUT,
	APPEND,
	HEREDOC,
	LIMITER,
	FD,
} t_type;

typedef enum e_error
{
	Q_ERROR = -1,
	PIPE_ERROR = -2,
	MISSING_FILENAME = -3,
	INVALID_OPERATOR = -4,
	NO_COMMAND = -5,
} t_error;

typedef struct s_tool
{
	char pwd[PATH_MAX];
	char old_pwd[PATH_MAX];
} t_tool;

typedef struct s_redirections
{
	char *name;
	int type;
	struct s_redirections *next;
} t_redirections;

typedef struct s_cmd
{
	char **argv;
	char *infile;
	char *outfile;
	int append;
	int heredoc;
	t_redirections *redirections;
	struct s_cmd *next;
	struct s_cmd *previous;
} t_cmd;

typedef struct s_save_fd
{
	int	save_stdin;
	int	save_stdout;
	int	infile;
	int	outfile;
} t_fd;

typedef struct s_obj
{
	t_token *token;
	t_cmd *cmd;
	t_tool *tool;
	t_fd	*fd;
	char **env;
	char *input;
	int *pid;
	int exit_code;
} t_obj;

typedef struct s_builtin
{
	char *name;
	int (*function)(t_obj *obj);
} t_builtin;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

/* ********* srcs ************* */
int main(int argc, char *argv[], char **envp);
void ctrl_c_inside_child(int signal);

/* ********* parsing ********** */
bool parsing(t_obj *obj);
void quote_error(char *str);
int check_quotes(char *str);
void track_quotes(char c, bool *s_quote, bool *d_quote);
void quote_removal(t_token *token);
char *remove_quotes(char *str);
t_token *tokenize(char *str);
int check_syntax(t_token *head);
t_cmd *create_cmd(t_obj *obj);
t_redirections *handle_redirections(t_token *token);

/* ********* expand ********** */
int nb_quote(char *str);
char *expand_var(char *str, char **envp);
int is_expand(char *str);
char *after_dollar(char *str, int *i, char **envp);
char *get_value(char *var_name, char **envp);
int check_char(char c);
char *special_case(char *str, int *i);
char *join_and_free(char *s1, char *s2);
char *expand_it(char *str, char **envp);
char *get_varname(char *str, int *i, int start);

/* ********* execute ********** */
void execute(t_obj *obj);
char *get_absolute_path(t_cmd *cmd, char **env);
char *get_env_variable(char **env, char *variable);
void set_redirections(t_obj *obj, int *infile,
					  int *outfile);
bool create_files(t_obj *obj);
bool open_fd(t_cmd *cmd, int *input_fd, int *output_fd, char **envp);
int here_doc(char *limiter, char **envp);
char *get_next_line(int fd);

/* ********* builtins ********** */
int (*is_builtin(char *cmd))(t_obj *obj);
int run_single_builtin_safely(t_obj *obj);
int run_cd(t_obj *obj);
int ft_echo(t_obj *obj);
int run_env(t_obj *obj);
int run_unset(t_obj *obj);
int run_pwd(t_obj *obj);

/* ***** linked list utils **** */
t_redirections *append_redirections(t_redirections *head,
									t_redirections *node);
t_cmd *append_cmd(t_cmd *head, t_cmd *node);
t_token *append_token(t_token *head, t_token *node);

/* ***** cleanup function ***** */
void free_token(t_token *token);
void free_redirections(t_redirections *red);
void free_cmd(t_cmd *cmd);
void free_obj(t_obj *obj);
void ft_clear_tab(char **tab);
char *ft_clear(char **array);

/* ***** display functions ***** */
void display_error_message(int error_code, char *error_message);
int redirection_error(char *str);
void print_cmd(t_cmd *cmd);
void print_list(t_token *list);

/* ***** envp functions ***** */
char **clone_env(char **envp);
void search_line(char *str, t_obj *obj);
void unset_it(t_obj *obj, int i, int len);
int ft_tabcount(char **tab);
int clone(t_obj *obj, char **clone, int a);
void ft_freetab(char **tab);
void free_tab(char **tab, int i);
void sort_env(char **tab);
int ft_strcmp(char *s1, char *s2);

int check_export(char *arg);
int is_same_var_exp(char *env, char *cmd);
int clone_and_replace(t_obj *obj, char **clone, int a);
int clone_and_add(t_obj *obj, char **clone, int a);
int run_export(t_obj *obj);
void ft_freetab(char **tab);

/* ***** builtin cmd functions ***** */
int check_option(char **av);
int check_cd(char **agrv);

/* **** signal **** */
void    normal_signal(void);
void    in_exec_signal(void);
void    child_signal(void);
void    handle_normal_sigint(int sig);
void    handle_exec_sigint(int sig);
void    handle_sigquit(int sig);
void handle_sigchld(int sig);

#endif
