/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:50:46 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* cerca di eseguire i comandi built-in, ovvero i comandi che vengono gestiti direttamente dalla shell senza creare un nuovo processo. Questa funzione prende in input un token e la struttura t_all che contiene le informazioni principali della shell. 
**controlla il valore del primo elemento del token e se corrisponde ad uno dei comandi built-in disponibili (echo, env, unset, pwd, cd, export) esegue la funzione corrispondente.*/
void	ft_search_builtin(t_type *token, t_all *main)
{
	if (ft_strcmp(token->value[0], "echo") || \
			ft_strcmp(token->value[0], "/bin/echo"))
		ft_check_echo(token);
	else if (ft_strcmp(token->value[0], "env"))
		ft_check_env(token, main);
	else if (ft_strcmp(token->value[0], "unset"))
		ft_check_unset(token, main);
	else if (ft_strcmp(token->value[0], "pwd") || \
			ft_strcmp(token->value[0], "/bin/pwd"))
		ft_check_pwd(token);
	else if (ft_strcmp(token->value[0], "cd"))
		ft_check_cd(token, main);
	else if (ft_strcmp(token->value[0], "export"))
		ft_check_export(token, main);
}

/*viene utilizzata per eseguire i comandi built-in. 
**crea un nuovo processo utilizzando la funzione fork(). 
**Se il comando è "exit", viene eseguita la funzione ft_check_exit() per gestire l'uscita dalla shell. 
**Altrimenti, nel processo figlio, la funzione ft_search_builtin() viene chiamata per eseguire il comando built-in corrispondente.
**Se il token contiene un pipe, viene utilizzato il file descriptor restituito dalla funzione pipe() per la comunicazione tra i processi. 
**a funzione restituisce il token aggiornato.*/
t_type	*ft_execute_builtin(t_type *token, t_all *main)
{
	pid_t	pidchild;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		perror(RED"ERRORE2"COLOR_RES);
	ft_start_execute_(main);
	if (ft_strcmp(token->value[0], "exit"))
		ft_check_exit(token);
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
		ft_search_builtin(token, main);
		ft_store_matrix(main);
		exit(0);
	}
	token = ft_end_execute_(token, fd_pipe, main);
	return (token);
}
