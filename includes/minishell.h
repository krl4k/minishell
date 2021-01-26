/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:35 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 12:54:41 by mwinter          ###   ########.fr       */
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
# define FLAG_NONE	0b000000000
# define ECHO		0b000000001
# define CD			0b000000010
# define PWD		0b000000100
# define EXPORT		0b000001000
# define UNSET		0b000010000
# define ENV		0b000100000
# define EXIT		0b001000000


typedef struct s_all
{
	char echo[5];
	char cd[3];
	char 

}				t_all;
/*
** for init any variables
*/
void			init_all(t_all *all);


/*
** execute function
**
*/
int				execute(t_all *all, char *command,char **argv, char **env);

#endif
