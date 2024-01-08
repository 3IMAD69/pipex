/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:08:33 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/08 11:24:50 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh_bonus.h"

void	handle_command_helper(char **cmds, char **env)
{
	char	**paths;
	char	*workin_path;

	paths = get_path_from_env(env);
	if (paths == NULL && free_tab(cmds))
		print_error("PATH ENV NOT FOUND");
	else
	{
		workin_path = get_valid_path(paths, cmds[0]);
		if (workin_path == NULL && free_tab(cmds))
			print_error("Command not found");
		execute_command(workin_path, cmds, env);
	}
}

void	handle_command(char *arg, char **env)
{
	char	**cmds;

	cmds = ft_split(arg, ' ');
	if (ft_strnstr(cmds[0], "/", ft_strlen(cmds[0])))
	{
		if (access(cmds[0], X_OK) == -1 && free_tab(cmds))
			print_error("no such file or directory");
		else
			execute_command(cmds[0], cmds, env);
	}
	else
		handle_command_helper(cmds, env);
}

int	reopen_file(char *name)
{
	int	tmp_fd;

	tmp_fd = open(name, O_RDONLY);
	if (tmp_fd == -1)
		print_error("Error reading tmp file !!");
	return (tmp_fd);
}
