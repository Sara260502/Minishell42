/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:31:50 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_lstadd_back(t_type **lst, t_type *new)
{
	t_type	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}

/*t_type	*ft_lstlast(t_type *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_lstadd_back(t_type **lst, t_type *new)
// {
// 	t_type	*temp;

// 	if (new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		temp = ft_lstlast(*lst);
// 		temp->next = new;
// 		new->prev = temp;
// 	}
// }*/
