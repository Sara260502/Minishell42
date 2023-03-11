/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:49:30 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*gestisce l'ordine di priorità dell'esecuzione dei comandi all'interno del parser. 
**esegue i comandi in ordine di priorità, partendo dal livello più basso e salendo man mano. 
**Se un comando contiene un'assegnazione di variabile di ambiente, viene eseguita la funzione ft_execute_enviroment per gestire la variabile. 
**Se ci sono ridirezioni di input/output, viene eseguita la funzione ft_redirections. In caso contrario, viene eseguita la funzione ft_execute_exeve per eseguire il comando.*/
#include "../../../inc/minishell.h"

t_type	*ft_priority(t_type *token, int lvl, t_all *main)
{
	int		lstsize;

	lstsize = ft_lstsize_this(token);
	while (main->count <= lstsize)
	{
		if (token->priority != lvl)
			token = ft_priority(token, token->priority, main);
		if (ft_strchr(token->value[0], '=') && ft_check_envi(token->value[0]))
			token = ft_execute_enviroment(token, token->value[0]);
		else if (token->main->redirections)
			token = ft_redirections(token, token->main);
		else
			token = ft_execute_exeve(token, main);
		main->count++;
	}
	return (token);
}
