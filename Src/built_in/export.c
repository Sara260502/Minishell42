/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:40:08 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se l'esecuzione del comando export ha avuto successo, controllando la variabile res del token. 
**Se res è 0, significa che il comando è stato eseguito correttamente e la funzione non fa nulla. 
**Altrimenti, la funzione chiama la funzione ft_export per gestire l'errore.*/
void	ft_export_or(t_type *token, t_all *main)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				;
		}
	}
	else
		ft_export(token, main);
}

/*controlla se ci sono operatori logici and e or presenti nella linea di comando. 
**Se il token precedente contiene l'operatore or, la funzione chiama la funzione ft_export_or per gestire il caso in cui il comando export non sia andato a buon fine. 
**Se l'operatore precedente è and, la funzione controlla la variabile res del token per decidere se chiamare la funzione exit con codice 1 o la funzione ft_export per gestire l'errore. 
**Se non ci sono operatori precedenti, la funzione chiama semplicemente la funzione ft_export per eseguire il comando export.*/
void	ft_check_export(t_type *token, t_all *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_export_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_export(token, main);
		}
		else
			ft_export(token, main);
	}
	else
		ft_export(token, main);
}
