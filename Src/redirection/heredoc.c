/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:06:33 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*main->expand == false -> no expand dollar
main->expand == true -> expand dollar*/

/*scrive un input dell'utente in un file descriptor specifico, fino a quando non incontra una certa stringa "limiter". 
**se "expand" è 0, l'input dell'utente viene controllato per la presenza del carattere '$' e se lo trova, viene effettuata un'espansione heredoc chiamando la funzione ft_expand_heredoc. 
**viene deallocata la memoria utilizzata per la variabile "str"*/
int	ft_write_fd(int fd, char *limiter, t_all *main)
{
	char	*str;

	main->expand = ft_strchr(limiter, '"');
	limiter = ft_strtrim2(limiter, '"');
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(limiter, str) == 1)
			break ;
		if (main->expand == 0)
		{
			if (ft_strchr(str, '$') == 1)
				str = ft_expand_heredoc(str, main);
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free(str);
	return (0);
}

/*cambia il nome del file all'interno della struct "t_type" a seconda del carattere di redirezione specificato ("<' o '>'), analizzando la linea di comando.*/
void	ft_change_name_file(t_all *main, t_type *token, char redir)
{
	int		start;
	char	*tmp;
	int		end;

	start = ft_strlen(main->copy_line);
	end = 1;
	while (main->copy_line[start] != redir)
		start--;
	start++;
	while (main->copy_line[start] == 32 \
			&& main->copy_line[start])
		start++;
	while (main->copy_line[start + end] != 32 \
			&& main->copy_line[start + end])
		end++;
	tmp = ft_substr(main->copy_line, start, end);
	free(token->name_file);
	token->name_file = ft_strdup(tmp);
	free(tmp);
}

/*crea un nuovo file ".heredoc", scrive l'input dell'utente all'interno del file utilizzando la funzione ft_write_fd, quindi lo apre in modalità lettura/scrittura e duplica il file descriptor di input standard (STDIN_FILENO) con il file descriptor del file ".heredoc". 
**Se c'è anche un carattere di redirezione ">", il nome del file nella struct "t_type" viene modificato di conseguenza. 
**In caso di errore nell'apertura del file, viene stampato un messaggio di errore e il programma termina.*/
void	ft_heredoc(t_type *token, t_all *main)
{
	int		fd;
	char	*n_file;

	token->dup = dup(STDIN_FILENO);
	n_file = ".heredoc";
	free(token->name_file);
	token->name_file = NULL;
	ft_search_redir(token, "<<");
	fd = open (n_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_write_fd(fd, token->name_file, main);
	fd = open (n_file, O_RDWR);
	dup2(fd, STDIN_FILENO);
	if (ft_set_bool_redir(token, ">"))
		ft_change_name_file(main, token, '>');
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		g_exit = 1;
		exit(1);
	}
}

/*cerca e restituisce il nome di un file all'interno di una stringa, eliminando il nome dalla stringa originale.*/
char	*ft_find_name_file(char *str)
{
	int		start;
	int		end;
	int		delete;
	char	*rtr;

	start = 0;
	end = 0;
	while (str[start] == 32)
		start++;
	while (str[start + end] != 32 && str[start + end])
		end++;
	rtr = ft_substr(str, start, end);
	delete = start + end;
	while (delete != -1)
		str[delete--] = 127;
	return (rtr);
}
