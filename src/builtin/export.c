/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:49 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 16:48:49 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

static int	print_export_ht(t_simple_cmd *cmd)
{
	char	**array_env;
	char	*eq;
	int		i;

	if (cmd->args_num != 0)
		return (0);
	array_env = sort_hashtable(g_shell->env_global);
	i = 0;
	while (array_env[i])
	{
		eq = ft_strchr(array_env[i], '=');
		array_env[i][eq++ - array_env[i]] = 0;
		printf("declare -x %s=\"%s\"\n", array_env[i], eq);
		i++;
	}
	free_2d_array(array_env);
	return (1);
}

int	ft_export(t_simple_cmd *cmd)
{
	int		i;
	char	*eq;

	if (print_export_ht(cmd))
		return (errno);
	i = -1;
	while (++i < cmd->args_num)
	{
		eq = ft_strchr(cmd->cmd_args[i], '=');
		if (eq)
			cmd->cmd_args[i][eq++ - cmd->cmd_args[i]] = 0;
		else
			eq = find_hashtable(g_shell->env_local, cmd->cmd_args[i]);
		if (!is_variable_valid(cmd->cmd_args[i]))
		{
			errno = error_manager(ERRT_EXPORT_ERR, cmd->cmd_args[i], 1);
			continue ;
		}
		if (eq)
			insert_hashtable(g_shell->env_global, cmd->cmd_args[i], eq);
	}
	return (errno);
}
