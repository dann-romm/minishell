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

	src = init_source(input);
	if (!src)
		return (0);
	token = get_next_token(src);
	if (!token)
	{

	}
		return (0);
	while (token->type != T_EOF)
	{
		push_front_token_list(&list, init_token_list(token));
		token = get_next_token(src);
	}
	free(token->value);
	free(token);
	free(src->buffer);
	free(src->str);
	free(src);
}

int	push_front_token_list(t_token_list **head, t_token_list *node)
{
	if (!head || !node)
		return (1);
	node->next = *head;
	*head = node;
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
