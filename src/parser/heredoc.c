#include "shell.h"
#include "prompt.h"
#include "readline/readline.h"
#include "libft_funcs.h"

// if there is a heredoc, writes input into HEREDOC_FILENAME file
// and fills t_command_table fields
void	handle_heredoc(t_command_table *table)
{
	const char	*limiter = table->redirect._stdin;
	int			fd;
	char		*str;

	if (!limiter || table->redirect.is_stdin_append == 0)
		return ;
	fd = open(HEREDOC_FILENAME, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	table->redirect._stdin = ft_strdup(HEREDOC_FILENAME);
	str = prompt2();
	while (str && ft_strcmp(str, (char *)limiter))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = prompt2();
	}
	if (str)
		free(str);
	close(fd);
}
