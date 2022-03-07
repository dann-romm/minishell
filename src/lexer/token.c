#include "lexer.h"
#include "shell.h"

t_token_list	*token_list_init(t_token *token)
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

t_token_list	*token_list_create(char *input)
{
	// t_source		*src;
	// t_token			*token;
	// t_token_list	*list;

	// src = init_source(input);
	// token = get_next_token(src);
	// while (token->type != T_EOF)
	// {=
	// 	token = get_next_token(src);
	// }
	// free(src->buffer);
	// free(src->str);
	// free(src);
}

int	token_list_push_front(t_token_list **head, t_token_list *node)
{
	if (!head || !node)
		return (1);
	node->next = *head;
	*head = node;
	return (0);
}

int	token_list_clear(t_token_list **head)
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
