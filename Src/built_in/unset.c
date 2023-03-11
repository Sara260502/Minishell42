/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:42:35 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*rimuove dalle variabili di ambiente (contenute in main->export_env) quelle il cui nome corrisponde ai valori contenuti nell'array di stringhe token->value*/
void	ft_unset_exp(t_type *token, t_all *main)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = 0;
		while (main->export_env[j])
		{
			if (ft_strncmp(token->value[i], main->export_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(main->export_env[j]);
				main->export_env[j] = NULL;
				while (main->export_env[j + 1])
				{
					main->export_env[j] = main->export_env[j + 1];
					j++;
				}
				main->export_env[j] = NULL;
			}
			j++;
		}
		i++;
	}
}

/*rimuove le variabili d'ambiente specificate dai token presenti nell'array token, sia dall'array main->copy_env (che contiene le variabili d'ambiente non esplicitamente marcate come esportabili) che dall'array main->export_env (che contiene le variabili d'ambiente marcate come esportabili).*/
void	ft_unset(t_type *token, t_all *main)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = -1;
		while (main->copy_env[++j])
		{
			if (ft_strncmp(token->value[i], main->copy_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(main->copy_env[j]);
				main->copy_env[j] = NULL;
				while (main->copy_env[j + 1])
				{
					main->copy_env[j] = main->copy_env[j + 1];
					j++;
				}
				main->copy_env[j] = NULL;
			}
		}
		i++;
	}
	ft_unset_exp(token, main);
}

/*controlla se l'operazione di unset ha successo o meno*/
void	ft_echo_unset(t_type *token, t_all *main)
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
		ft_unset(token, main);
}

/*segue l'operazione di unset in base al token precedente, controllando anche gli operatori logici "or" e "and".*/
void	ft_check_unset(t_type *token, t_all *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_echo_unset(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_unset(token, main);
		}
		else
			ft_unset(token, main);
	}
	else
		ft_unset(token, main);
}
