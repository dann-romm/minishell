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
		push_back_token_list(&list, init_token_list(token));
		token = get_next_token(src);
	}
	free(token->value);
	free(token);
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

int	remove_token_list(t_token_list *head, t_token_list **node)
{
	t_token_list	*tmp;

	if (!(*node)->next)
	{
		while (head && head->next != (*node))
			head = head->next;
		free((*node)->token->value);
		free((*node)->token);
		free((*node));
		*node = NULL;
		head->next = NULL;
		return (0);
	}
	free((*node)->token->value);
	free((*node)->token);
	(*node)->token = (*node)->next->token;
	tmp = (*node)->next->next;
	free((*node)->next);
	(*node)->next = tmp;
	return (0);
}

int	clear_token_list(t_token_list **head)
{
	t_token_list	*tmp;

	if (!head)
		return (1);
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		free(tmp->token->value);
		free(tmp->token);
		free(tmp);
	}
	return (0);
}
