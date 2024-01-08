/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:34:18 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/08 10:12:53 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh_bonus.h"

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
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
		if (buffer == NULL)
			break ;
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
	tmp_fd = reopen_file("tmp");
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

void	handle_last_command(char *cmd, char **env, int input_fd, int outfile_fd)
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
		if (dup2(outfile_fd, STDOUT_FILENO) == -1 && close(fd[1]))
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

int	main_helper(int argc, char **argv, int *input_fd, int *outfile_fd)
{
	if (argc < 5)
		print_error("Invalid Number of Argument !!");
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1) == 0)
	{
		if (argc < 6)
			print_error("Invalid Number of Argument to use here_doc !");
		*input_fd = handle_here_doc(argv);
		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (2);
	}
	else
	{
		*input_fd = open(argv[1], O_RDONLY);
		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (1);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	input_fd;
	int	outfile_fd;

	i = main_helper(argc, argv, &input_fd, &outfile_fd);
	if (input_fd == -1 || outfile_fd == -1)
		print_error("Error opening in/out  file!");
	dup2(input_fd, STDIN_FILENO);
	while (++i < argc - 1)
	{
		if (i == argc - 2)
			handle_last_command(argv[i], env, input_fd, outfile_fd);
		else
			handle_mutiple_pipes(argv[i], env, input_fd, outfile_fd);
	}
	close(input_fd);
	close(outfile_fd);
	while (wait(NULL) > 0)
		;
	unlink("tmp");
	return (0);
}
