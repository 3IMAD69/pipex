
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:34:18 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/01 11:21:28 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh.h"

int	print_error(char *str)
{
	printf("%s \n", str);
	exit(1);
}

void child_func(int fd_write,char *input_file)
{
	int input_fd;

	input_fd = open(input_file,O_RDONLY);
	if (input_fd == -1)
		print_error("Error opening the input file!");
	if (dup2(input_fd,STDIN_FILENO) == -1)
		print_error("Error dup2");
	// if (dup2(fd_write,STDOUT_FILENO) == -1)
	// 	print_error("Error dup2");
	close(fd_write);
	printf("child executing %s \n",input_file);
}

void parent_func(int fd_read)
{
	close(fd_read);
}

char **get_path_from_env(char **env)
{
	int i;
	char **paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5,':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	int fd[2];
	pid_t pid;
	//0 read
	//1 write
	if (argc != 5)
		print_error("Invalid Number of Argument !!");
	const char *program = "/bin/ls";

	// int imak
    // Arguments for the ls command
    char *arggg[] = { "/bin/ls", "-l", NULL };
	//  if (execve(program, arggg, NULL) == -1) {
    //     print_error("execve");
    // }
	char **path = get_path_from_env(env);
	if (path == NULL)
		print_error("Error getting path from env");
	int i = 0;
	while (path[i] != NULL)
	{
		printf("%s\n", path[i]);
		if (access(ft_strjoin(path[i], "/ls"), X_OK) == -1)
		{
			printf("Command not found !!");
		}
		else
			printf("command Found in %s\n",path[i]);
		i++;
	}
	printf("Why this code doesnt get executed !!ma\n");
	// if (pipe(fd) == -1)
	// 	print_error("Error creating them pipe");
	// pid = fork(); 
	// if (pid == -1)
	// 	print_error("Error while forking !!");   
	// if (pid == 0)
	// 	child_func(fd[1],argv[1]);
	// else
	// 	parent_func(fd[0]);
	return (0);
}
