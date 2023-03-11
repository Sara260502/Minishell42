/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:32:33 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_type *lst_or)
{
	int		c;
	t_type	*cpy;

	c = 0;
	cpy = ft_return_head(lst_or);
	while (cpy)
	{
		c++;
		cpy = cpy->next;
	}
	return (c);
}

int	ft_lstsize_this(t_type *lst_or)
{
	int		c;
	t_type	*cpy;

	c = 0;
	cpy = lst_or;
	while (cpy)
	{
		if (cpy->next && cpy->priority == cpy->next->priority)
			c++;
		cpy = cpy->next;
	}
	return (c);
}
