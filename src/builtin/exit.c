/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:42:56 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 01:51:42 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_funcs.h"

static void	delete_shell(void)
{
	delete_hashtable(&(g_shell->env_global));
	delete_hashtable(&(g_shell->env_local));
	free(g_shell);
}

static int	is_str_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_numeric(str[i]))
			return (0);
	}
	return (1);
}

int	ft_exit(char **cmd_args, int args_num)
{
	printf("exit\n");
	if (args_num == 0)
	{
		delete_shell();
		exit(errno);
	}
	else if (args_num == 1)
	{
		delete_shell();
		if (!is_str_numeric(cmd_args[0]))
		{
			errno = error_manager(ERRT_NUM_ARG, cmd_args[0], 255);
			exit(errno);
		}
		else
			exit(ft_atoi(cmd_args[0]));
	}
	else
		errno = error_manager(ERRT_MANY_ARG, "-42", 1);
	return (errno);
}
