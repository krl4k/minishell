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
# include "../srcs/libft/libft.h"
# include <errno.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MALLOC_ERROR "malloc error!"

typedef struct  s_all
{
	unsigned int pwd;
    unsigned int cd;
    unsigned int echo;
    unsigned int export;
    unsigned int unset;
    unsigned int env;
    unsigned int exit;
    unsigned int bin_command;
	char			**command_argv;

}				t_all;
/*
** for init any variables
*/
void			init_all(t_all *all);


/*
** execute function
**
*/
int				execute(t_all *all, char *line, char **argv, char **env);
//int				execute(t_all *all, char **argv, char **env);

#endif
