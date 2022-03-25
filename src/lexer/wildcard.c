#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

void	handle_wildcard(t_source *src)
{
	char	*str;

	while (is_alnum(peek(src)) || peek(src) == '_' || peek(src) == '.' || peek(src) == '/')
		save_char(src, next_char(src));
	str = ft_strdup(src->str);
	
}
