/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:35:35 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla il numero di argomenti e esce dal programma*/
void	ft_exit(t_type *token)
{
	int	i;
	int	num;

	i = 0;
	while (token->value[i])
		i++;
	if (i > 2)
	{
		g_exit = 1;
		printf("Exit\n");
		perror(RED ERROR_EXIT COLOR_RES);
	}
	else if (token->value[1] == NULL)
	{
		printf(RED "\texit\n" COLOR_RES);
		ft_free_token(token);
		exit(0);
	}
	else
	{
		num = ft_atoi(token->value[1]);
		printf(RED "\texit\n" COLOR_RES);
		ft_free_token(token);
		exit(num);
	}
}

/*esegue l'uscita solo se il risultato è diverso da zero*/
void	ft_exit_or(t_type *token)
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
		ft_exit(token);
}

/*controlla se il token precedente è un operatore logico e, a seconda del tipo, esegue ft_exit_or, ft_exit o esce dal programma con uno stato di errore*/
void	ft_check_exit(t_type *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_exit_or(token);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_exit(token);
		}
		else
			ft_exit(token);
	}
	else
		ft_exit(token);
}
