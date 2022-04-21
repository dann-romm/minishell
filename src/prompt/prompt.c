/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:58:46 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 16:50:52 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "libft_funcs.h"

char	*prompt1(void)
{
	char	*input;

	input = readline(find_hashtable(g_shell->env_local, "PS1"));
	if (!input)
	{
		rl_redisplay();
		exit(130);
	}
	return (input);
}

char	*prompt2(void)
{
	return (readline(find_hashtable(g_shell->env_local, "PS2")));
}
