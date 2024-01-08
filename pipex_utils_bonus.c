/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:17:39 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/08 11:25:28 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh_bonus.h"

char	**get_path_from_env(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*join_strings(char *str1, char *str2, char *str3)
{
	int		size;
	char	*new_str;

	size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	new_str = (char *)malloc(sizeof(char) * size);
	ft_strlcpy(new_str, str1, size);
	ft_strlcat(new_str, str2, size);
	ft_strlcat(new_str, str3, size);
	return (new_str);
}

char	*get_valid_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = join_strings(paths[i], "/", cmd);
		if (access(tmp, X_OK) != -1 && free_tab(paths))
			return (tmp);
		free(tmp);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (1);
}

void	execute_command(char *path, char **args, char **env)
{
	if (execve(path, args, env) == -1)
	{
		if (path != args[0])
			free(path);
		free_tab(args);
		print_error("Command not found");
	}
	else
	{
		if (path != args[0])
			free(path);
		free_tab(args);
	}
	exit(0);
}
