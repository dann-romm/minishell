#include "shell.h"

void	ft_echo(char **args)
{
	if (ft_strcmp(args[0], "-n") == 0)
		write(1, args[1], ft_strlen(args[1]));
	else
	{
		write(1, args[1], ft_strlen(args[1]));
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	//char **all_builtins[] =
	//{
	//	{"cd", ft_cd},
	//	{"echo", ft_echo},
	//	{"env", ft_env},
	//	{"pwd", ft_pwd},
	//};

	//ft_pwd();
	char **args[2];
	args[0] = "-n";
	args[1] = "echo $PATH";
	ft_echo(args);
	go_to_path("HOME", env);
	//ft_env(env);
}
