/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:05:33 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 14:00:18 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*cerca il primo token (cioè la prima parola) nella stringa line, delimitata da spazi o parentesi aperta, restituendo la stringa che rappresenta il resto della linea (cioè line senza il primo token).
**la funzione aggiunge il primo token alla lista concatenata di token presente nella struttura t_all. 
**Se il parametro booleano first è true, la lista concatenata viene sostituita con il nuovo token, altrimenti il nuovo token viene aggiunto in coda alla lista. 
**La funzione utilizza le funzioni ft_substr, ft_lstnew e ft_lstadd_back per creare e gestire i nodi della lista concatenata di token.*/
char	*ft_find_token(char *line, t_all *main, bool first)
{
	int		start;
	char	*command;
	char	*rtr;
	int		end;

	start = 0;
	end = 0;
	while (line[start] == ' ' || line[start] == '(')
		start++;
	while (line[start + end] != ' ' && line[start + end] != '\0')
		end++;
	command = ft_substr(line, start, end);
	if (first)
	{
		free(main->token);
		main->token = ft_lstnew(command, main);
	}
	else
		ft_lstadd_back(&main->token, ft_lstnew(command, main));
	free(command);
	rtr = ft_substr(line, start + end, ft_strlen(line));
	return (rtr);
}
