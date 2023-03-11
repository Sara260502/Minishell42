/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:32:29 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_type	*ft_lstnew(void *content, t_all *main)
{
	t_type	*nlist;

	nlist = (t_type *)malloc(sizeof(t_type));
	if (!nlist)
		return (NULL);
	nlist->command = ft_strdup(content);
	nlist->value = NULL;
	nlist->priority = 0;
	nlist->res = 0;
	nlist->dup = STDIN_FILENO;
	nlist->stdinput = STDIN_FILENO;
	nlist->output = STDOUT_FILENO;
	nlist->or = false;
	nlist->and = false;
	nlist->pipe = false;
	nlist->input = false;
	nlist->append = false;
	nlist->output = false;
	nlist->heredoc = false;
	nlist->name_file = NULL;
	nlist->main = main;
	nlist->prev = NULL;
	nlist->next = NULL;
	return (nlist);
}
