/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:31:01 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/05 09:44:27 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeh_bonus.h"

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}