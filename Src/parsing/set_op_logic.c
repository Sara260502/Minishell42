/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_op_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:05:43 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 14:00:30 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*cerca il primo operatore logico & o | nella stringa line a partire dalla posizione i e restituisce l'indice della posizione dell'operatore trovato.*/
int	ft_support_set_op(char *line, int i, t_type *token)
{
	while (line[i])
	{
		i = ft_check_double_quote(line, token->main, i);
		i = ft_check_single_quote(line, token->main, i);
		if (line[i] == '&' || line[i] == '|')
			break ;
		i++;
	}
	return (i);
}

/*imposta gli operatori logici (and, or, pipe) per ogni token nella lista concatenata token a seconda dell'operatore trovato nella stringa line. 
**scorre tutti i token della lista, usa la funzione ft_support_set_op per trovare l'operatore logico corrispondente e imposta il flag dell'operatore nel token corrispondente*/
void	ft_set_op_logic(char *line, t_type *token)
{
	int	i;

	i = 0;
	token = ft_return_head(token);
	while (token)
	{
		i = ft_support_set_op(line, i, token);
		i++;
		if (line[i] == '&')
			token->and = true;
		else if (line[i] == '|')
			token->or = true;
		else if (line[i - 1] == '|' && line[i] != '|')
			token->pipe = true;
		i++;
		if (!token->next)
			break ;
		token = token->next;
	}
}
