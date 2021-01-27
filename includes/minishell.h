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


# define RED "[1;31m"
# define GREEN "[1;32m"
# define BLUE "[1;34m"
# define BG_RED "[1;41m"
# define BG_BLUE "[1;44m"
# define END "\033[0m"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MALLOC_ERROR "malloc error!"

typedef struct		s_all
{
	unsigned int	c_pwd;
    unsigned int	c_cd;
    unsigned int	c_echo;
    unsigned int	c_export;
    unsigned int	c_unset;
    unsigned int	c_env;
    unsigned int	c_exit;
    unsigned int	c_bin_command;
	char			**command_argv;
	char            **av;
	char            **env;
}					t_all;
/*
** for init any variables
*/
void			init_all(t_all **all);

/*!
** promt kaomoji its cute!!!
*/
void			print_prompt(void);

/*
** execute function
**
*/
int             execute(t_all *all);
//int			execute(t_all *all, char **argv, char **env);
void			bin_func(t_all *all);



#endif
