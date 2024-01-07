/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:34:18 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/07 18:53:53 by idhaimy          ###   ########.fr       */
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
		free(workin_path);
		free_tab(paths);
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

int	handle_here_doc(char **argv)
{
	char	*buffer;
	char	*tmp;
	int		tmp_fd;

	tmp_fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		print_error("Error opening tmp file !!");
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (buffer == NULL)
			break;
		tmp = ft_strtrim(buffer, "\n");
		if (ft_strncmp(tmp, argv[2], ft_strlen(buffer)) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, tmp_fd);
		free(buffer);
	}
	close(tmp_fd);
	tmp_fd = open("tmp", O_RDONLY);
	if (tmp_fd == -1)
		print_error("Error reading tmp file !!");
	return (tmp_fd);
}

void	handle_mutiple_pipes(char *cmd, char **env, int input_fd,
		int outfile_fd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		print_error("Error creating them pipe");
	pid = fork();
	if (pid == -1)
		print_error("Error while forking !!");
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1 && close(fd[1]))
			print_error("Error dup2");
		close(fd[1]);
		close(input_fd);
		close(outfile_fd);
		handle_command(cmd, env);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1 && close(fd[0]))
			print_error("Error dup2 second parent dup2");
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	input_fd;
	int	outfile_fd;

	i = 1;
	if (argc < 5)
		print_error("Invalid Number of Argument !!");
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (argc < 6)
			print_error("Invalid Number of Argument to use here_doc !");
		input_fd = handle_here_doc(argv);
		ft_putstr_fd(ft_itoa(input_fd), 2);
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		i = 2;
	}
	else
	{
		input_fd = open(argv[1], O_RDONLY);
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (input_fd == -1 || outfile_fd == -1)
		print_error("Error opening in/out  file!");
	dup2(input_fd, STDIN_FILENO);
	while (++i < argc - 2)
		handle_mutiple_pipes(argv[i], env, input_fd, outfile_fd);
	dup2(outfile_fd, STDOUT_FILENO);
	close(input_fd);
	close(outfile_fd);
	while (wait(NULL) > 0)
		;
	unlink("tmp");
	handle_command(argv[argc - 2], env);
	return (0);
}
