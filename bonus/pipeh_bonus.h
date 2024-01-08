/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeh_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 09:46:33 by idhaimy           #+#    #+#             */
/*   Updated: 2024/01/08 15:31:20 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEH_BONUS_H
# define PIPEH_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	**get_path_from_env(char **env);
char	*get_valid_path(char **paths, char *cmd);
int		free_tab(char **tab);
char	*join_strings(char *str1, char *str2, char *str3);
int		free_tab(char **tab);
void	execute_command(char *path, char **args, char **env);
int		print_error(char *str);
void	handle_command_helper(char **cmds, char **env);
void	handle_command(char *arg, char **env);
int		reopen_file(char *name);
int		close_fds(int fd1, int fd2, int fd3);
#endif