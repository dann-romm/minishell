#include "lexer.h"
#include "shell.h"
#include "libft_funcs.h"

#include "debug.h" // to remove

t_token	*init_token(t_token_type type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		errno = ENOMEM;
		return (NULL);
	}
	token->type = type;
	if (str)
		token->value = ft_strdup(str);
	else
		token->value = NULL;
	if (str && !token->value)
	{
		errno = ENOMEM;
		return (NULL);
	}
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

t_token_list	*init_token_list(t_token *token)
{
	t_token_list	*node;
	
	node = (t_token_list *)malloc(sizeof(t_token_list));
	if (!node)
	{
		errno = ENOMEM;
		return (NULL);
	}
	node->token = token;
	node->next = NULL;
	return (node);
}

t_token_list	*create_token_list(char *input)
{
	t_source		*src;
	t_token			*token;
	t_token_list	*list;

	list = NULL;
	src = init_source(input);
	if (!src)
		return (0);
	token = get_next_token(src);
	if (!token)
	{
		delete_source(&src);
		return (0);
	}
	while (token->type != T_EOF)
	{
		if (token->type == T_ERROR) // raise error
		{
			delete_token(&token);
			delete_source(&src);
			delete_token_list(&list);
			return (0);
		}
		push_back_token_list(&list, init_token_list(token));
		token = get_next_token(src);
	}
	delete_token(&token);
	delete_source(&src);
	return (list);
}

int	push_back_token_list(t_token_list **head, t_token_list *node)
{
	t_token_list	*tmp;

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

int	remove_token_list(t_token_list **head, t_token_list **node)
{
	if (!head || !(*head) || !node || !(*node))
		return (1);
	delete_token(&((*node)->token));
	if (!(*node)->next)
	{
		if (*head == *node)
		{
			free(*head);
			*head = NULL;
			return (0);
		}
		while (*head && (*head)->next != (*node))
			head = &((*head)->next);
		free(*node);
		*node = NULL;
		(*head)->next = NULL;
		return (0);
	}
	(*node)->token = (*node)->next->token;
	head = &((*node)->next->next);
	free((*node)->next);
	(*node)->next = *head;
	return (0);
}

int	delete_token_list(t_token_list **head)
{
	t_token_list	*tmp;

	if (!head)
		return (1);
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		delete_token(&(tmp->token));
		free(tmp);
	}
	return (0);
}
