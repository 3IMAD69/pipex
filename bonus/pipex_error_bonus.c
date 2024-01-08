/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:31:01 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/08 15:35:51 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh_bonus.h"

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int	close_fds(int fd1, int fd2, int fd3)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (fd3)
		close(fd3);
	return (1);
}
