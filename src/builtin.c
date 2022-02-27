#include "../includes/shell.h"

//void ft_cd(char **path)
//{
//	//Printing the current working directory - getcwd()
//	if (path == 0)
//		chdir("..");
//	else
//		chdir(path);
//}

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

void	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void ft_pwd()
{
	char *cur_dir;
	cur_dir = (char *)malloc(sizeof(char) * 257);
	cur_dir = getcwd(cur_dir, 257);
	printf("%s\n", cur_dir);
	free(cur_dir);
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
	args[1] = "hiii";
	ft_echo(args);
	//ft_env(env);
}
