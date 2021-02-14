/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:35 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:44:36 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "dirent.h"
# include "sys/stat.h"
# include "dynamic_array.h"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MALLOC_ERROR "malloc error!"
# define PROMT_ERROR "ヽ(*・ω・)ﾉ: \0"
# define READ 0
# define WRITE 1
# define IS_SPACE(x) (x==' '||x =='\t'||x=='\r'||x=='\f'||x =='\v'||x=='\n')

int g_exit_code;

typedef struct		s_all
{
	char			**command_argv;
	char			*old_home;
	char			*old_pwd;
	char			*input;
	char			**old_path;
	t_array			*env_array;
	char			*in_path;
	char			*out_path;
	int				count_redir;
	int				input_redir_flag;
	int				output_redir_flag;
	int				append_redir_flag;
	int				l_pipe[2];
	int				r_pipe[2];
	int				*arg_location;
	int				pipes;
	int				input_file_descriptor;
	int				output_file_descriptor;
	int				status;
	int				i;
	int				k;
}					t_all;

/*
** for init any variables
*/

void				init_all(t_all **all, char **env);
void				error_handler(int type_error);

/*
** prompt kaomoji its so cute!!!
** @param file descriptor
*/

void				print_prompt(int fd);
/*
** execute function
*/

void				signals_init(int mode);
int					execute(t_all *all);
char				*check_bin_func(t_all *all, char *cmd);
void				ft_echo(char **cmd);

/*
** cd command
*/

int					ft_cd(t_all *all);
void				chdir_error(t_all *all);
char				*home(t_all *all);
void				home_not_set(t_all *all, char **h);
void				oldpwd_not_set(t_all *all);
int					not_path_cd(t_all *all, char **h);
void				new_pwd(t_all *all);
void				save_oldpwd(t_all *all);

/*
** pwd
*/

void				ft_pwd(char **cmd);
int					ft_env(t_all *all);
void				ft_exit(char **cmd);
int					check_n(char *flag, int *i);

/*
** export && unset
*/

int					ft_export(t_all *all);
int					check_valid_argv(char *key);
void				check_zero(t_all *all, int i);
int					check_valid_key(t_all *all,
					char *new_env, int i, int ret_v);
void				error_mes(char *command);
int					ft_unset(t_all *all);
int					ft_export_print_sort_env(t_all *all);

/*
** pipes
*/

int					pipes_work(t_all *all);
int					input_redir_init(t_all *all, int index);
int					output_redir_init(t_all *all);
int					append_redir_init(t_all *all);
void				pipes_fd_init(t_all *all, int index);
void				count_redir(t_all *all);
void				set_flags(t_all *all, char **path, int *flag, int count);
int					count_command(t_all *all);
int					execute_commands(t_all *all);
void				init_handler_pipes(t_all *all);
void				free_handler_pipes(t_all *all);
void				ft_execution(t_all *all);
char				*get_env_by_key(t_all *all, char *key);
void				print_error(t_all *all);
void				check_env(t_all *all);
char				*get_env(char *line, t_all *all);
int					key_len(char *line, t_all *all);
int					check_controls(t_all *all);

/*
** parser func
*/

char				**ft_realloc_args(char **p, int new_size);
int					size_arr(char **cmd);
int					is_numeric(char *cmd);
char				*get_controls(char *line, t_all *all);
char				*get_in_quotes(char *line, t_all *all);
void				*syntax_error(char *error);
char				*get_word(char *line, t_all *all);
int					parse_line(char *line, t_all *all);
char				*get_input(void);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoinchar(char *str, char c);
void				substitution_env(t_all *all);
void				get_commands(t_all *all, char *line);

#endif
