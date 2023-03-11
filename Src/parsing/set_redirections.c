/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:06:04 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 14:00:41 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*riceve in input un puntatore a un token e una stringa redir, che rappresenta la sequenza di caratteri che si vuole cercare all'interno del token. 
**utilizza un ciclo while per scorrere l'array value di token e cerca redir all'interno di ogni elemento dell'array utilizzando la funzione ft_strcmp. 
**Se redir viene trovato in uno degli elementi dell'array, la funzione imposta il nome del file nel token successivo e ritorna 1. 
**Altrimenti, la funzione ritorna 0.*/
int	ft_search_redir(t_type *token, char *redir)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], redir))
		{
			if (!token->name_file)
				token->name_file = ft_strdup(token->value[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*simile alla prima, ma non imposta il nome del file successivo se redir viene trovato.
**Invece, ritorna 1 se redir viene trovato all'interno di uno degli elementi dell'array value di token, altrimenti ritorna 0.*/
int	ft_set_bool_redir(t_type *token, char *redir)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], redir))
			return (1);
		i++;
	}
	return (0);
}

/*controlla ogni token e imposta i flag dei token in base alla presenza di determinate sequenze di caratteri*/
void	ft_set_redirections(t_type *token)
{
	token = ft_return_head(token);
	while (token)
	{
		if (ft_search_redir(token, ">") == 1)
			token->output = true;
		if (ft_search_redir(token, ">>") == 1)
			token->append = true;
		if (ft_search_redir(token, "<") == 1)
			token->input = true;
		if (ft_set_bool_redir(token, "<<") == 1)
			token->heredoc = true;
		if (!token->next)
			break ;
		token = token->next;
	}
}
