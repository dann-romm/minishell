/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:34:31 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 16:48:34 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "hashtable.h"
#include "builtin.h"
#include "libft_funcs.h"

void	upd_pwd(char *path)
{
	insert_hashtable(g_shell->env_global, "OLDPWD",
		find_hashtable(g_shell->env_global, "PWD"));
	insert_hashtable(g_shell->env_global, "PWD", path);
}

void	change_dir(t_simple_cmd *cd)
{
	char	*cur_dir;

	if (chdir(cd->cmd_args[0]))
	{
		if (access(cd->cmd_args[0], F_OK) == -1)
		{
			errno = 2;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
		}
		else if (access(cd->cmd_args[0], R_OK) == -1)
		{
			errno = 13;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
		}
		else
		{
			errno = 20;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
		}
	}
	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, PATH_MAX);
	upd_pwd(cur_dir);
	free(cur_dir);
}

int	ft_cd(t_simple_cmd *cd)
{
	const char	*path = getenv("HOME");

	if (!cd->args_num)
	{
		chdir(path);
		upd_pwd((char *)path);
	}
	else
		change_dir(cd);
	return (errno);
}
