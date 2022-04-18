#include "lexer.h"
#include "shell.h"
#include "libft_funcs.h"

t_token	*init_token(t_token_type type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (str)
		token->value = ft_strdup(str);
	else
		token->value = NULL;
	if (str && !token->value)
		return (NULL);
	token->next = NULL;
	return (token);
}

int	delete_token(t_token **token)
{
	if (!token || !(*token))
		return (1);
	if ((*token)->value)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	free(*token);
	*token = NULL;
	return (0);
}

int	push_back_token_list(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (!head || !node)
		return (1);
	if (!(*head))
	{
		*head = node;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (0);
}

int	remove_token_list(t_token **head, t_token **node)
{
	if (!head || !(*head) || !node || !(*node))
		return (1);
	if (!(*node)->next)
	{
		if (*head == *node)
		{
			delete_token(head);
			return (0);
		}
		while (*head && (*head)->next != (*node))
			head = &((*head)->next);
		delete_token(node);
		(*head)->next = NULL;
		return (0);
	}
	(*node)->type = (*node)->next->type;
	free((*node)->value);
	(*node)->value = (*node)->next->value;
	head = &((*node)->next->next);
	free((*node)->next);
	(*node)->next = *head;
	return (0);
}

int	delete_token_list(t_token **head)
{
	t_token	*tmp;

	if (!head)
		return (1);
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		delete_token(&tmp);
	}
	return (0);
}
