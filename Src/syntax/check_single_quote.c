/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:27 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se il carattere corrente della stringa line è una singola virgoletta. 
**In caso affermativo, incrementa il contatore main->sin_quotes e scorre la stringa fino a trovare la corrispondente chiusura dell'apice singolo, incrementando nuovamente il contatore e uscendo dal ciclo while.
**restituisce l'indice del carattere successivo all'ultimo carattere dell'apice singolo trovato. 
**Questo indice viene utilizzato successivamente per riprendere il controllo della stringa line dal carattere successivo a quello dell'ultimo apice singolo trovato.*/
int	ft_check_single_quote(char *line, t_all *main, int i)
{
	if (line[i] == 39)
	{
		main->sin_quotes++;
		i++;
		while (line[i])
		{
			if (line[i] == 39)
			{
				main->sin_quotes++;
				break ;
			}
			i++;
		}
	}
	return (i);
}
