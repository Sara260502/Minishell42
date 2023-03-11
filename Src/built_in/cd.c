/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:29:05 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*aggiorna la variabile d'ambiente PWD con il percorso corrente della directory di lavoro.*/
void	cd_path(t_all *main)
{
	int		i;
	char	*tmp;

	i = 0;
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0)
		{
			tmp = getcwd(NULL, 0);
			free(main->copy_env[i]);
			main->copy_env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

/*cambia la directory di lavoro in base al secondo argomento passato (o alla directory home se non viene specificato alcun argomento), poi chiama cd_path per aggiornare PWD.*/
void	ft_cd(t_type *token, t_all *main)
{
	char	*tmp;

	if (token->value[1] == NULL)
	{
		tmp = getenv("HOME");
		chdir(tmp);
		cd_path(main);
	}
	else if (chdir(token->value[1]) == -1)
	{
		g_exit = 1;
		printf(RED"cd: %s: " ERROR_FILE COLOR_RES, token->value[1]);
		printf("\n");
	}
	else
		cd_path(main);
}

/*controlla se la variabile res del token precedente è uguale a 0 (che indica l'assenza di errori nella precedente esecuzione di un comando), in tal caso esegue la funzione ft_cd.*/
void	ft_cd_or(t_type *token, t_all *main)
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
		ft_cd(token, main);
}

/*esegue la funzione ft_cd se il token precedente non ha alcuna logica booleana associata (ossia né and né or), altrimenti chiama ft_cd_or se il token precedente ha associato il valore or, altrimenti esegue ft_cd solo se res è uguale a 0.*/
void	ft_check_cd(t_type *token, t_all *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_cd_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_cd(token, main);
		}
		else
			ft_cd(token, main);
	}
	else
		ft_cd(token, main);
}
