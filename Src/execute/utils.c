/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:02:33 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*viene chiamata quando il processo genitore esegue il comando, chiude la pipe, aspetta che il figlio termini e imposta la variabile globale "g_exit" con il valore di uscita del figlio.*/
void	ft_parent_execute_(t_type *token, pid_t pidchild, int fd_pipe[2])
{
	close(fd_pipe[1]);
	waitpid(pidchild, &token->res, 0);
	if (WIFEXITED(token->res))
		g_exit = WEXITSTATUS(token->res);
}

/*viene chiamata all'inizio dell'esecuzione del comando e crea due file temporanei ".help" e ".export" utilizzati per memorizzare variabili d'ambiente e funzioni che vengono eseguite durante l'esecuzione del comando.*/
void	ft_start_execute_(t_all *main)
{
	char	*tmp;

	tmp = ft_strjoin(main->files_pwd, ".help");
	main->fd_matrix = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
	tmp = ft_strjoin(main->files_pwd, ".export");
	main->fd_export = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(tmp);
}

/*viene chiamata alla fine dell'esecuzione del comando e ripristina l'ambiente, legge i valori di variabili d'ambiente e funzioni dai file temporanei e restituisce il puntatore al token successivo.*/
t_type	*ft_end_execute_(t_type *token, int fd_pipe[2], t_all *main)
{
	if (token->next)
	{
		token = token->next;
		token->res = token->prev->res;
		token->dup = token->prev->dup;
	}
	if (token->prev && token->prev->pipe && token->stdinput == STDIN_FILENO)
	{
		token->dup = dup(STDIN_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);
		token->stdinput = fd_pipe[0];
		close(fd_pipe[0]);
	}
	else if (token->stdinput != token->dup)
		dup2(token->dup, STDIN_FILENO);
	ft_free_matrix(main->copy_env);
	ft_free_matrix(main->export_env);
	main->copy_env = ft_get_next_line(main->fd_matrix, \
			ft_strjoin(main->files_pwd, ".help"));
	main->export_env = ft_get_next_line(main->fd_export, \
			ft_strjoin(main->files_pwd, ".export"));
	return (token);
}

/*viene utilizzata per salvare le variabili di ambiente dell'applicazione in due file separati, uno chiamato .help e l'altro chiamato .export. 
**Vengono aperti i due file e, per ogni variabile di ambiente presente nelle rispettive matrici, viene scritto il contenuto del file con un carattere di newline alla fine di ogni variabile*/
void	ft_store_matrix(t_all *main)
{
	int		i;

	i = 0;
	while (main->copy_env[i])
	{
		write(main->fd_matrix, main->copy_env[i], ft_strlen(main->copy_env[i]));
		write(main->fd_matrix, "\n", 1);
		i++;
	}
	close(main->fd_matrix);
	i = 0;
	while (main->export_env[i])
	{
		write(main->fd_export, main->export_env[i],
			ft_strlen(main->export_env[i]));
		write(main->fd_export, "\n", 1);
		i++;
	}
	close(main->fd_export);
}

/*viene utilizzata per controllare la variabile di ambiente PWD (presente nella matrice main->copy_env) e, se la directory corrente non corrisponde al percorso salvato in questa variabile, la funzione cambia la directory corrente tramite la funzione chdir().*/
void	ft_check_dir(t_all *main)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0)
		{
			free(pwd);
			pwd = ft_substr(main->copy_env[i], 4, ft_strlen(main->copy_env[i]));
			chdir(pwd);
		}
		i++;
	}
	free(pwd);
}
