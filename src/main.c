#include "shell.h"

// void	test_init_source()
// {
// 	t_source	*src = init_source("echo \"hello world\"");
// 	printf("%c %c %c %c %c\n", peek(src), peek2(src), next_char(src), next_char(src), peek2(src));
// }

void	print_token(t_token *token)
{
	char	*str_token_type = malloc(100);
	switch (token->type)
	{
		case T_EOF:
			str_token_type = "T_EOF";
			break;
		case T_ERROR:
			str_token_type = "T_ERROR";
			break;
		case T_NUMBER:
			str_token_type = "T_NUMBER";
			break;
		case T_ID:
			str_token_type = "T_ID";
			break;
		case T_DOLLAR:
			str_token_type = "T_DOLLAR";
			break;
		case T_STRING:
			str_token_type = "T_STRING";
			break;
		case T_EXITSTATUS:
			str_token_type = "T_EXITSTATUS";
			break;
		case T_IF:
			str_token_type = "T_IF";
			break;
		case T_THEN:
			str_token_type = "T_THEN";
			break;
		case T_ELSE:
			str_token_type = "T_ELSE";
			break;
		case T_ELIF:
			str_token_type = "T_ELIF";
			break;
		case T_FI:
			str_token_type = "T_FI";
			break;
		case T_FOR:
			str_token_type = "T_FOR";
			break;
		case T_IN:
			str_token_type = "T_IN";
			break;
		case T_BREAK:
			str_token_type = "T_BREAK";
			break;
		case T_CONTINUE:
			str_token_type = "T_CONTINUE";
			break;
		case T_WHILE:
			str_token_type = "T_WHILE";
			break;
		case T_DO:
			str_token_type = "T_DO";
			break;
		case T_DONE:
			str_token_type = "T_DONE";
			break;
		case T_AND:
			str_token_type = "T_AND";
			break;
		case T_ANDAND:
			str_token_type = "T_ANDAND";
			break;
		case T_PIPE:
			str_token_type = "T_PIPE";
			break;
		case T_OROR:
			str_token_type = "T_OROR";
			break;
		case T_LESS:
			str_token_type = "T_LESS";
			break;
		case T_GREAT:
			str_token_type = "T_GREAT";
			break;
		case T_EQUALS:
			str_token_type = "T_EQUALS";
			break;
		case T_DGREAT:
			str_token_type = "T_DGREAT";
			break;
		case T_DLESS:
			str_token_type = "T_DLESS";
			break;
		case T_LESSAND:
			str_token_type = "T_LESSAND";
			break;
		case T_GREATAND:
			str_token_type = "T_GREATAND";
			break;
		case T_LESSGREAT:
			str_token_type = "T_LESSGREAT";
			break;
		case T_DLESSDASH:
			str_token_type = "T_DLESSDASH";
			break;
		case T_CLOBBER:
			str_token_type = "T_CLOBBER";
			break;
		case T_SEMI:
			str_token_type = "T_SEMI";
			break;
		case T_DSEMI:
			str_token_type = "T_DSEMI";
			break;
		case T_TICK:
			str_token_type = "T_TICK";
			break;
		case T_NEWLINE:
			str_token_type = "T_NEWLINE";
			break;
		default:
			str_token_type = "(null)";
			break;
	}

	printf("token:\n   type:  %s\n   value: %s\n", str_token_type, token->value);
}

int	main(int argc, char **argv, char **env)
{
	t_source	*src = init_source("&& $? <> <<");
	// t_source	*src = init_source("   \t &? << printf ; | pipe || `qwe` ;; 123");
	t_token		*token;

	token = get_next_token(src);
	print_token(token);
	token = get_next_token(src);
	print_token(token);
	token = get_next_token(src);
	print_token(token);
}
