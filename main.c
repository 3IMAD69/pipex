
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
	exit(0);
}

void child_func(int fd_write)
{
	write(fd_write,"KYS",4);
	close(fd_write);
	printf("child executing \n");
}

void parent_func(int fd_read)
{g
	char tab[4];
	read(fd_read,tab,4);
	close(fd_read);
	printf("Message => %s \n",tab);
	printf("parent executing\n");
}

int	main(int argc, char **argv)
{
	int fd[2];
	pid_t pid;
	//0 read
	//1 write
	if (argc != 5)
		print_error("Invalid Number of Argument !!\n");
	if (pipe(fd) == -1)
		print_error("Error creating them pipe\n");
	pid = fork(); 
	if (pid == -1)
		print_error("Error while forking !!");   
	if (pid == 0)
		child_func(fd[1]);
	else
		parent_func(fd[0]);
}

