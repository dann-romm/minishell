/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:16:34 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 21:16:35 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

int	ft_unset(t_simple_cmd *unset_cmd)
{
	int		i;

	i = -1;
	if (!unset_cmd->args_num)
		return (0);
	else if (check_input(unset_cmd->cmd_args[0]))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", \
			unset_cmd->cmd_args[0]);
		errno = 1;
		return (errno);
	}
	else
	{
		while (++i < unset_cmd->args_num)
		{
			if (find_hashtable(g_shell->env_global, unset_cmd->cmd) != 0)
				remove_hashtable(&(g_shell->env_global), unset_cmd->cmd);
		}
	}
	return (0);
}
