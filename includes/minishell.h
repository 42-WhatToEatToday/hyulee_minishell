/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:45:03 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/30 14:36:13 by kyoukim          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/time.h>

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# define QUOTE				(1 << 0)
# define DQUOTE				(1 << 1)

# define MAX_PATH_LENGTH	1000
# define MAX_STR			1000
# define MAX_COM			100

# define NOT_A_BUILTIN		0

# define READ_END			0
# define WRITE_END			1

typedef struct		s_cmd
{
	char			*command;
	char			**argv;
	int				argv_num;
}					t_cmd;

typedef struct 		s_env
{
	char 			*key;
	char 			*value;
	struct s_env 	*next;
}					t_env;

typedef struct		s_tok
{
	char			**tokens;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_cmds
{
	t_tok			*tokens;
	struct s_cmds	*next;
}					t_cmds;

typedef struct		s_state
{
	t_env			*env_head;
	t_cmds			*cmds;
	t_cmds			*curr_cmds;
	char			*input;
}					t_state;

void	frees(void *s1, void *s2, void *s3);
void	free_array(char **arrs);
void	free_command(t_cmds **cmds);
void	free_tok(t_tok **tok);

t_env	*find_env(t_env **head, char *key);
t_env	*create_new_env(char *key, char *value);
void	change_env(t_env **head, char *key, char *value);
void	add_list_back(t_env **head, char *key, char *value);
void	delete_env(t_env **head, char *key);
void	seperate_key_value(char *argv, char **key, char **value);

void	free_envp(char **envp);
char	**get_envp(t_env **head);

void	sigint_handler(int signo);
void	sigquit_handler(int signo);

void	prompt(t_state *s, char **envp);

int		tokenize(t_cmds *cmds, char **piped);
int		get_tok_size(t_tok *tok);
t_tok	*create_tok(char **data);
void	append_tok(t_tok **tok, t_tok *new);

void	parse_line(t_state *s, char *input);

t_cmds	*create_command(t_tok *data);
void	append_command(t_cmds **cmds, t_cmds *new);

char	**split_delimiter(char *s, char c);

int		execute_pipe(t_state *s, int read, int write, char **envp);
int		execute(t_state *s, char **envp);

void	ft_env(t_state *s);
void	ft_export(t_state *s, t_cmd cmd);
void	ft_unset(t_state *s, t_cmd cmd);

#endif
