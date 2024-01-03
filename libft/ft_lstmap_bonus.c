/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhaimy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:31:42 by idhaimy           #+#    #+#             */
/*   Updated: 2023/11/15 16:19:20 by idhaimy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newlist;
	t_list	*newnode;
	void	*tmp_cont;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	current = lst;
	while (current != NULL)
	{
		tmp_cont = f(current->content);
		newnode = ft_lstnew(tmp_cont);
		if (!newnode || !tmp_cont)
		{
			free(tmp_cont);
			free(newnode);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&newlist, newnode);
		current = current->next;
	}
	return (newlist);
}

// #include <stdio.h>

// void	del(void *content)
// {
// 	free (content);
// }

// void	*f(void	*content)
// {
// 	return ((void *) ft_strdup((char *)content+5));
// }

// void printlist(t_list *lst)
// {
// 	while(lst)
// 	{
// 		printf("%s \n",(char *)lst->content);
// 		lst = lst->next;
// 	}
// }

// int main()
// {
// 	t_list *head = NULL;
// 	t_list *newList = NULL;

// 	t_list *node1 = ft_lstnew(ft_strdup("node 1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("node 2"));
// 	t_list *node3 = ft_lstnew(ft_strdup("node 3"));

// 	ft_lstadd_back(&head,node1);
// 	ft_lstadd_back(&head,node2);
// 	ft_lstadd_back(&head,node3);

// 	printlist(head);
// 	newList = ft_lstmap(head,f,del);
// 	printlist(newList);

// }