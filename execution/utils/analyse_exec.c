/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenbajj <mbenbajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:56:27 by mbenbajj          #+#    #+#             */
/*   Updated: 2022/07/05 14:51:37 by mbenbajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution.h"

int	analyse_red_io(t_shell *shell, t_data *elem)
{
	int		fd;

	fd = 0;
	if (elem->str && elem->token == RIP)
		fd = open(elem->str, O_RDONLY, 0666);
	else if (elem->str && elem->token == ROP)
		fd = open(elem->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (elem->str && elem->token == APND)
		fd = open(elem->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0 || !elem->str)
	{
		error_cmd_arg(&shell->env, "Minsishell", elem->str, NSFD);
		shell->data = shell->data->next;
		return (-1);
	}
	else if (fd > 0)
	{
		if (elem->token == RIP)
			dup2(fd, 0);
		else if (elem->token == ROP || elem->token == APND)
			dup2(fd, 1);
		// close(fd);
		shell->data = shell->data->next;
	}
	return (fd);
}

int	analyse_cmd(t_shell *shell, t_data *elem)
{
	char	*cmd_path;
	
	if (elem->str && elem->token == CMD)
	{
		cmd_path = NULL;
		if (!if_cmd_builtin(shell->cmd->cmd_flags[0]))
		{
			cmd_path = get_cmd_path(shell->env, shell->cmd->cmd_flags[0]);
			if (!cmd_path)
				return (-1);
		}
		proccess_cmd(shell, shell->cmd->cmd_flags[0], cmd_path);
		if (cmd_path)
			free(cmd_path);
		shell->cmd = shell->cmd->next;
	}
	return (0);
}

int	analyse_exec_buff(t_shell *shell, t_data *elem)
{
	int	fd;

	fd = analyse_red_io(shell, elem);
	if (fd == -1 || analyse_cmd(shell, elem) == -1)
		return (-1);
	// close (fd);
	return (0);
}
