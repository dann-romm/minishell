/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:16:34 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 02:21:23 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

int	ft_unset(t_simple_cmd *cmd)
{
	int	i;

	if (!cmd->args_num)
		return (0);
	i = 0;
	while (i < cmd->args_num)
	{
		if (!is_variable_valid(cmd->cmd_args[i]))
			errno = error_manager(ERRT_UNSET_ERR, cmd->cmd_args[i], 1);
		else
		{
			if (find_hashtable(g_shell->env_global, cmd->cmd_args[i]))
				remove_hashtable(g_shell->env_global, cmd->cmd_args[i]);
		}
		i++;
	}
	return (errno);
}
