/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:16:34 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 21:42:55 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

int	ft_unset(t_simple_cmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd->args_num)
		return (0);
	while (i < cmd->args_num)
	{
		if (check_input(cmd->cmd_args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", \
				cmd->cmd_args[i]);
			errno = 1;
		}
		else
		{
			if (find_hashtable(g_shell->env_global, cmd->cmd_args[i]) != 0)
				remove_hashtable(g_shell->env_global, cmd->cmd_args[i]);
		}
		i++;
	}
	return (errno);
}
