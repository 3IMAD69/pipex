/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:25:41 by idhaimy           #+#    #+#             */
/*   Updated: 2023/11/15 15:59:01 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*llast;

	if (!lst || !new)
		return ;
	llast = ft_lstlast(*lst);
	if (llast == NULL)
		*lst = new;
	else
		llast->next = new;
}
