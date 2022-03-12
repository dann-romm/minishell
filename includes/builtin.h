#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(t_hashtable *ht, t_simple_cmd *cd);
void	ft_echo(char **args, int arg_num);
void	ft_env();
int		ft_exit();
void	ft_export(t_simple_cmd *cd);
void	ft_pwd(t_hashtable *ht);
void	ft_unset(t_simple_cmd *unset_cmd);

#endif
