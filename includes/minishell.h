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

#if !defined MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"

# define RED "[1;31m"
# define GREEN "[1;32m"
# define BLUE "[1;34m"
# define BG_RED "[1;41m"
# define BG_BLUE "[1;44m"
# define END "\033[0m"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MALLOC_ERROR "malloc error!"
# define PROMT_ERROR "ヽ(*・ω・)ﾉ: \0"
# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\r' || x == '\f' || x == '\v' || x == '\n')

typedef struct		s_all
{
    unsigned int	c_bin_command;
	char			**command_argv;
	char            **av;
	char            **env;
	char			*old_home;
	int				env_count;
}					t_all;

/*!
** for init any variables
*/

void			init_all(t_all **all, char **env);

/*!
** prompt kaomoji its so cute!!!
** @param file descriptor
*/
void			print_prompt(int fd);

/*!
** execute function
*/

int             execute(t_all *all);
void			bin_func(t_all *all);
void            ft_echo(char **cmd);
int				ft_cd(t_all *all);
int				ft_env(t_all *all);
int             check_n(char *flag, int *i);
int				check_quotes(char *str);

#endif
