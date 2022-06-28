/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenbajj <mbenbajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:42:31 by mbenbajj          #+#    #+#             */
/*   Updated: 2022/06/25 20:55:36 by mbenbajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

int	ft_pwd(t_shell *shell)
{
	t_env	*env;
	char	*path;
	char	cwd[PATH_MAX];

	env = shell->env;
	while (env)
	{
		if (!ft_strcmp("PWD", env->var))
			break ;
		env = env->next;
	}
	if (env)
		path = env->value;
	else
		path = getcwd(cwd, sizeof(cwd));
	// if (!path)
		// error PWD not set
	printf("%s\n", path);
	return (0);
}