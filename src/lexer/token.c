#include "lexer.h"
#include "shell.h"

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
