/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:49 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/22 19:38:07 by mgwyness         ###   ########.fr       */
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
	array_env = hashtable_to_sorted_array(g_shell.env_global);
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
	int		is_eq;

	if (print_export_ht(cmd))
		return (errno);
	i = -1;
	while (++i < cmd->args_num)
	{
		is_eq = 0;
		eq = ft_strchr(cmd->cmd_args[i], '=');
		if (eq)
			cmd->cmd_args[i][eq++ - cmd->cmd_args[i]] = is_eq++;
		else
			eq = find_hashtable(g_shell.env_local, cmd->cmd_args[i]);
		if (!is_variable_valid(cmd->cmd_args[i]))
		{
			if (is_eq)
				*(--eq) = '=';
			errno = error_manager(ERRT_EXPORT_ERR, cmd->cmd_args[i], 1);
		}
		else if (eq)
			insert_hashtable(g_shell.env_global, cmd->cmd_args[i], eq);
	}
	return (errno);
}
