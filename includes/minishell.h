/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:45:03 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 15:47:30 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/time.h>

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# define QUOTE				0x00000001
# define DQUOTE				0x00000002
# define TOKENIZE			0x00000004
# define REDI_IN			0x00000008
# define REDI_OUT			0x00000010
# define BACKSLASH			0x00000020

# define MAX_PATH_LENGTH	1000
# define MAX_STR			1000
# define MAX_COM			100

# define NOT_A_BUILTIN		0

# define COMMAND_ERROR		1
# define PATH_ERROR			2
# define SYNTAX_ERROR			3
# define NOFILE_ERROR			4

# define READ_END			0
# define WRITE_END			1

typedef struct		s_cmd
{
	char			*command;
	char			**argv;
	int				argv_num;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_tok
{
	char			**tokens;
	int				flag;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_cmds
{
	t_tok			*tokens;
	t_tok			*curr_tok;
	struct s_cmds	*next;
}					t_cmds;

typedef struct		s_state
{
	t_env			*env_head;
	t_cmds			*cmds;
	t_cmds			*curr_cmds;
	char			*input;
	int				waiting;
	int				exitnum;
	int				rd_fd;
	int				wrt_fd;
	int				flag;
}					t_state;

/*
** Main functions
*/
void				prompt(t_state *s, char **envp);
void				parse_line(t_state *s, char *input);

/*
** Command functions
*/
int					ft_echo(t_state *s, t_cmd cmd);
int					ft_cd(t_state *s, t_cmd cmd);
int					ft_pwd(t_state *s);
int					ft_env(t_state *s);
int					ft_export(t_state *s, t_cmd cmd);
int					ft_unset(t_state *s, t_cmd cmd);
int					ft_exit();

/*
** Functinos related to executing commands
*/
void				execute(t_state *s, char **envp);
int					execute_cmd(t_state *s, char **envp);
int					execute_builtin(t_state *s, t_cmd cmd);
int					init_cmd(t_state *s, t_cmd *cmd);
int					set_redirection(t_state *s);
int					search_token(t_state *s, char *c, int *i);
int					get_argv_num(t_cmd cmd);

/*
** Functions related to t_cmds
*/
t_cmds				*create_command(t_tok *data);
void				append_command(t_cmds **cmds, t_cmds *new);

/*
** Functions related to t_env
*/
t_env				*find_env(t_env **head, char *key);
t_env				*create_new_env(char *key, char *value);
void				change_env(t_env **head, char *key, char *value);
void				add_list_back(t_env **head, char *key, char *value);
void				delete_env(t_env **head, char *key);
void				seperate_key_value(char *argv, char **key, char **value);

/*
** Functions related to t_tok
*/
int					tokenize(t_cmds *cmds, char **piped);
int					get_tok_size(t_tok *tok);
t_tok				*create_tok(char **data);
void				append_tok(t_tok **tok, t_tok *new);

/*
** Functions related to envp
*/
void				free_envp(char **envp);
char				**get_envp(t_env **head);

/*
** Functions related to environment variables
*/
char				**handle_env_var(t_state *s, char **piped);

/*
** Functions related to signal
*/
void				sigint_handler(int signo);
void				sigquit_handler(int signo);

/*
** Functions related to handling strings
*/
void				remove_quotes_backslashes(t_tok *tok, char **tokens);
char				**split_delimiter(char *s, char c);
int					put_words_in_ret(char **ret, char *s, char c, int flag);

/*
** Functions related to paths
*/
char				**parse_path(t_state *s);
int					check_path(t_state *s, t_cmd *cmd);

/*
** Free functions
*/
void				frees(void *s1, void *s2, void *s3);
void				free_array(char **arrs);
void				free_command(t_cmds **cmds);
void				free_tok(t_tok **tok);
void				free_redirection(char **argv, int *index);

#endif
