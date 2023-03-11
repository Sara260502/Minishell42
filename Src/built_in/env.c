/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:33:40 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

/*stampa tutte le variabili d'ambiente presenti nella struttura "main"*/
void	ft_env(t_all *main)
{
	int	i;

	i = 0;
	while (main->copy_env[i])
	{
		printf("%s\n", main->copy_env[i]);
		i++;
	}
}

/*richiamata solo nel caso in cui il risultato dell'operazione precedente sia 0 (ossia il comando precedente è andato a buon fine), ma ci sia ancora un comando successivo e l'operatore logico corrispondente sia un "||".*/
void	ft_env_or(t_type *token, t_all *main)
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
		ft_env(main);
}

/*controlla la presenza di operatori logici (&& e ||) nel comando e richiama la funzione appropriata in base al risultato dell'operazione precedente*/
void	ft_check_env(t_type *token, t_all *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_env_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_env(main);
		}
		else
			ft_env(main);
	}
	else
		ft_env(main);
}
