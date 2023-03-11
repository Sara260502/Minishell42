/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:54:29 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*viene utilizzata per eseguire il comando dopo aver fatto tutti i controlli e le eventuali operazioni di redirezionamento.*/
void	ft_execute_redi(t_type *token, t_all *main)
{
	if (!main->token->heredoc)
		ft_execute_dollar(main->token, main);
	if (ft_strchr(main->token->value[0], '=') \
		&& ft_check_envi(main->token->value[0]))
		main->token = ft_execute_enviroment(main->token, main->token->value[0]);
	else if (ft_check_builtin(main->token) && !main->redirections)
		main->token = ft_execute_builtin(main->token, main);
	else
		main->token = ft_execute_exeve(main->token, main);
	ft_check_dir(main);
	exit(token->res);
}

/*esegue il parsing e l'esecuzione dei comandi passati in input.
**scorre la lista di token che rappresentano i comandi, eseguendo il parsing dei vari tipi di redirezionamento e, se non sono presenti, esegue il controllo se il comando è un builtin o no, 
**esegue il comando attraverso ft_execute_builtin o ft_execute_exeve*/
void	ft_execute_command(t_all *main)
{
	int	lstsize;

	main->count = 0;
	lstsize = ft_lstsize(main->token);
	main->token = ft_return_head(main->token);
	while (main->count < lstsize)
	{
		if (!main->token->heredoc)
			ft_execute_dollar(main->token, main);
		if (ft_strchr(main->token->value[0], '=') \
			&& ft_check_envi(main->token->value[0]))
			main->token = \
				ft_execute_enviroment(main->token, main->token->value[0]);
		else if (main->token->input || main->token->append || \
			main->token->output || main->token->heredoc || main->redirections)
			main->token = ft_redirections(main->token, main);
		else if (ft_check_builtin(main->token) && !main->redirections)
			main->token = ft_execute_builtin(main->token, main);
		else
			main->token = ft_execute_exeve(main->token, main);
		ft_check_dir(main);
		main->count++;
	}
}
