/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:06:50 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se ci sono ridirezioni dell'output (con token->output e token->append) e apre il file con i giusti flag. 
**Se l'apertura fallisce, viene stampato un messaggio di errore e il processo viene terminato. 
<<++Il file descriptor viene salvato in token->stdoutput e la funzione ft_set_bool_redir viene chiamata per controllare se ci sono altre ridirezioni di input.*/
void	ft_output_redirect(t_type *token, t_all *main)
{
	int	fd;

	fd = 0;
	token->dup = dup(STDOUT_FILENO);
	if (token->output == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (token->append == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		g_exit = 1;
		ft_free_token(token);
		exit(1);
	}
	token->stdoutput = fd;
	if (ft_set_bool_redir(token, "<"))
		ft_change_name_file(main, token, '<');
}

/*apre il file di input e lo collega allo standard input.*/
void	ft_input_redirect(t_type *token)
{
	int	fd;

	token->dup = dup(STDIN_FILENO);
	fd = open (token->name_file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		g_exit = 1;
		exit(1);
	}
	token->stdinput = fd;
}

/* rimuove i simboli di ridirezione dai token.*/
void	ft_delete_redirection(t_type *token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token->value[i])
		{
			if (ft_strcmp(token->value[i], "<") \
				|| ft_strcmp(token->value[i], "<<") \
				|| ft_strcmp(token->value[i], ">") \
				|| ft_strcmp(token->value[i], ">>"))
			{
				free(token->value[i]);
				token->value[i] = NULL;
			}
			i++;
		}
	}
}

/*esegue la ridirezione dell'output. Se ci sono più ridirezioni, la funzione ft_execute_multi_redir viene chiamata, altrimenti viene chiamata ft_single_redir.*/
void	ft_stdout(t_type *token, t_all *main)
{
	if (ft_count_redirection(token) > 1)
		ft_execute_multi_redir(token);
	else
		ft_single_redir(token, main);
	if (token->stdoutput != STDOUT_FILENO)
		dup2(token->dup, STDOUT_FILENO);
	else if (token->stdinput != STDIN_FILENO)
		dup2(token->dup, STDIN_FILENO);
}

/*esegue la ridirezione e aspetta il processo figlio. 
**Se ci sono più token, il puntatore viene spostato al token successivo e token->res viene impostato con il valore di ritorno del token precedente. 
**Il token modificato viene quindi restituito.*/
t_type	*ft_redirections(t_type *token, t_all *main)
{
	pid_t	pidchild;

	pidchild = fork();
	if (pidchild != 0)
	{
		waitpid(pidchild, &token->res, 0);
		if (WIFEXITED(token->res))
			g_exit = WEXITSTATUS(token->res);
	}
	else
		ft_stdout(token, main);
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
	}
	return (token);
}
