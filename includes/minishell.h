/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:35 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/25 20:27:47 by mwinter          ###   ########.fr       */
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

typedef struct s_all
{
	char **impl_builtin;

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
