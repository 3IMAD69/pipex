/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:34:18 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/05 20:08:18 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh.h"

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

void	child1_func(int *fd_child, char **av, char **env)
{
	int	input_fd;
	
	input_fd = open(av[1], O_RDONLY);
	close(fd_child[0]);
	if (input_fd == -1 && close(fd_child[1]))
		print_error("Error opening the input file!");
	if (dup2(input_fd, STDIN_FILENO) == -1 && close(fd_child[1]))
		print_error("Error dup2");
	if (dup2(fd_child[1], STDOUT_FILENO) == -1 && close(fd_child[1]))
		print_error("Error dup2");
	close(fd_child[1]);
	handle_command(av[2], env);
}

void	child2_func(int *fd_child2, char **av, char **env)
{
	int	outfile_fd;
	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd_child2[1]);
	if (outfile_fd == -1)
		print_error("Error opening the input file!");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1 && close(fd_child2[0]))
		print_error("Error dup2 first parent dup2");
	if (dup2(fd_child2[0], STDIN_FILENO) == -1 && close(fd_child2[0]))
		print_error("Error dup2 second parent dup2");
	close(fd_child2[0]);
	handle_command(av[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		print_error("Invalid Number of Argument !!");
	if (pipe(fd) == -1)
		print_error("Error creating them pipe");
	pid1 = fork();
	if (pid1 == -1)
		print_error("Error while forking !!");
	if (pid1 == 0)
		child1_func(fd, argv, env);
	pid2 = fork();
	if (pid2 == -1)
		print_error("Error while forking !!");
	if (pid2 == 0)
		child2_func(fd,argv,env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2,NULL,0);
	return (0);
}
