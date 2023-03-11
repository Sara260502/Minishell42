/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:36 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla che ci sia un numero uguale di parentesi aperte e chiuse nel comando. 
**Scorre il comando carattere per carattere e utilizza le funzioni ft_check_double_quote e ft_check_single_quote per ignorare i caratteri contenuti all'interno di doppi o singoli apici. 
**Se trova una parentesi aperta, incrementa il contatore main->open_brackets, se invece trova una parentesi chiusa, incrementa il contatore main->close_brackets. 
**Infine, controlla se i due contatori hanno lo stesso valore e se non lo hanno, imposta il flag main->error a true e stampa un messaggio di errore.*/
int	ft_check_brackets(char *line, t_all *main)
{
	int	i;

	i = -1;
	main->open_brackets = 0;
	main->close_brackets = 0;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == '(')
			main->open_brackets++;
		if (line[i] == ')')
		main->close_brackets++;
	}
	if (main->open_brackets > main->close_brackets)
	{
		main->error = TRUE;
		ft_putendl_fd(RED ERROR_OPEN_BRACKETS COLOR_RES, STDOUT_FILENO);
	}
	else if (main->open_brackets < main->close_brackets)
	{
		main->error = TRUE;
		ft_putendl_fd(RED ERROR_CLOSE_BRACKETS COLOR_RES, STDOUT_FILENO);
	}
	return (i);
}

/*esegue controlli sulla corretta apertura e chiusura di virgolette e backslash all'interno del comando e sulle variabili di espansione. 
**Se viene rilevato un errore, viene impostata una variabile di stato*/
void	ft_easy_synatx(char *line, t_all *main)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		if (main->dub_quotes % 2 != 0 && !main->error)
		{
			ft_putendl_fd(RED ERROR_DOUBLE_QUOTE COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		i = ft_check_single_quote(line, main, i);
		if (main->sin_quotes % 2 != 0 && !main->error)
		{
			ft_putendl_fd(RED ERROR_SING_QUOTE COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		if (line[i] == 92 && line[i] && !main->error)
		{
			ft_putendl_fd(RED ERROR_BACKSLASH COLOR_RES, STDOUT_FILENO);
			main->error = true;
		}
		if ((line[i] == 124 || line[i] == 38) && line[i])
			main->op_logic = true;
	}
}

/*controlla la corretta sintassi degli operatori logici (&& e ||) nel comando.*/
void	ft_check_operetor_logic(char *line, t_all *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == '&' || line[i] == '|')
		{
			if (line[i + 1] == '&' && line[i + 2] != '&')
				i++;
			else if ((line[i + 1] == '|' || line[i + 1] != '|') \
					&& line[i + 2] != '|' && line[i] != '&')
				i++;
			else
			{
				ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
				main->error = true;
				break ;
			}
		}
		i++;
	}
}

/* chiama le funzioni sopra elencate e controlla la presenza di errori di sintassi e in caso affermativo imposta una variabile di stato e imposta il codice di uscita della shell.*/
void	ft_check_syntax(char *line, t_all *main)
{
	main->error = false;
	main->dub_quotes = 0;
	main->sin_quotes = 0;
	main->redirections = false;
	main->expand = false;
	ft_easy_synatx(line, main);
	if (ft_strchr(line, '$') && !main->error)
		main->error = ft_expand_check(line);
	if (!main->error)
		ft_check_redirection(line, main);
	if (!main->error)
		ft_check_operetor_logic(line, main);
	if (main->op_logic && !main->error)
		ft_check_brackets(line, main);
	if (main->error == TRUE)
		g_exit = 258;
}
