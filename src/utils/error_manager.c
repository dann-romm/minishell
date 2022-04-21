/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:42 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 18:41:06 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"

int	error_manager(t_error_type type, const char *msg, int error_code)
{
	printf("minishell: ");
	if (type == ERRT_SYNTAX)
		printf("Syntax error near unexpected token `%s'\n", msg);
	else if (type == ERRT_PWD_ERR)
		printf("%s: %s\n", find_hashtable(g_shell.env_global, "PWD"),
			strerror(errno));
	else if (type == ERRT_CD_ERR)
		printf("cd: %s: %s\n", msg, strerror(errno));
	else if (type == ERRT_UNSUPPORTED)
		printf("`%s': Is not supported in this version of minishell\n", msg);
	else if (type == ERRT_NOT_FOUND)
		printf("%s: Command not found\n", msg);
	else if (type == ERRT_EXPORT_ERR)
		printf("export: `%s': not a valid identifier\n", msg);
	else if (type == ERRT_UNSET_ERR)
		printf("unset: `%s': not a valid identifier\n", msg);
	else if (type == ERRT_NUM_ARG)
		printf("exit: %s: Numeric argument required\n", msg);
	else if (type == ERRT_MANY_ARG)
		printf("exit: Too many arguments\n");
	else if (type == ERRT_ERRNO_ERR)
		printf("%s: %s\n", msg, strerror(errno));
	return (error_code);
}
