/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:41:31 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*utilizza la funzione di sistema getcwd per ottenere il percorso di lavoro corrente e lo stampa sulla console. Viene quindi deallocata la memoria allocata per il percorso di lavoro.*/
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

/*controlla se l'esito del comando precedente è stato positivo o negativo e decide se eseguire o meno la funzione ft_pwd chiamandola o ignorandola.*/
void	ft_pwd_or(t_type *token)
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
		ft_pwd();
}

/*controlla se il comando precedente era una pipe e, in caso contrario, controlla se l'esito del comando precedente è stato positivo o negativo e decide se eseguire o meno la funzione ft_pwd chiamandola o ignorandola.*/
void	ft_check_pwd(t_type *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_pwd_or(token);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_pwd();
		}
		else
			ft_pwd();
	}
	else
		ft_pwd();
}
