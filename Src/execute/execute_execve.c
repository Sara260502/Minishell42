/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:59:13 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*viene chiamata quando il token corrente è un "and" e il risultato della precedente esecuzione è stato positivo.*/
static void	ft_execve_and(t_type *token)
{
	if (token->res == 0)
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	exit(1);
}

/*viene chiamata quando il token corrente è un "or" e il risultato della precedente esecuzione è stato negativo*/
static void	ft_execve_or(t_type *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				exit(1);
		}
		exit(1);
	}
	if (execve(token->command, token->value, token->main->copy_env))
	{
		printf(RED"%s: coomand not found\n"COLOR_RES, token->value[0]);
		g_exit = 127;
		exit(127);
	}
}

/*viene chiamata quando il token corrente è un comando eseguibile e si occupa di eseguirlo con execve*/
static void	ft_exceve(t_type *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_execve_or(token);
		else if (token->prev->and)
			ft_execve_and(token);
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	else
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	exit(1);
}

/*si occupa di eseguire i comandi eseguibili. 
**Crea una pipe, avvia l'esecuzione e la gestione del processo figlio chiamando ft_start_execute_ e ft_parent_execute_, quindi chiama ft_exceve per eseguire il comando corrente. 
**chiama ft_end_execute_ per gestire la chiusura del processo figlio e restituisce il token successivo.*/
t_type	*ft_execute_exeve(t_type *token, t_all *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	ft_start_execute_(main);
	pidchild = fork();
	if (pidchild != 0)
		ft_parent_execute_(token, pidchild, fd_pipe);
	else
	{
		close(fd_pipe[0]);
		if (token->pipe)
		{
			dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[1]);
		}
		ft_store_matrix(main);
		ft_exceve(token);
	}
	token = ft_end_execute_(token, fd_pipe, main);
	return (token);
}
