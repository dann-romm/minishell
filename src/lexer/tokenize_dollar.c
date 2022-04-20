/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:04 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:01:05 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "libft_funcs.h"

static void	put_exit_status_into_src(t_source *src)
{
	const char	*exit_status = ft_itoa(g_shell->exit_status);
	int			i;

	if (!exit_status)
		return ;
	i = 0;
	while (exit_status[i])
		save_char(src, exit_status[i++]);
}

static void	put_env_into_src(t_source *src)
{
	t_source	*tmp;
	char		*key;
	char		*value;

	tmp = init_source("");
	if (is_numeric(peek(src)))
		save_char(tmp, next_char(src));
	else
	{
		while (is_alnum(peek(src)) || peek(src) == '_')
			save_char(tmp, next_char(src));
	}
	key = ft_strdup(tmp->str);
	value = find_hashtable(g_shell->env_global, key);
	clear_str(tmp);
	while (value && *value)
		save_char(src, *value++);
	free(key);
	delete_source(&tmp);
}

int	tokenize_dollar(t_source *src, t_token *token)
{
	int	require_bracket;

	if (peek(src) != '$')
		return (0);
	token->type = T_ID;
	require_bracket = 0;
	next_char(src);
	if (is_space(peek(src)))
		save_char(src, '$');
	else if (peek(src) == '?')
	{
		next_char(src);
		put_exit_status_into_src(src);
	}
	else
	{
		if (peek(src) == '{')
			require_bracket = 1 + (next_char(src) == -42);
		put_env_into_src(src);
		if (require_bracket && peek(src) != '}')
			token->type = T_ERROR;
		else if (require_bracket)
			next_char(src);
	}
	return (1);
}
