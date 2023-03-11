/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:38 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*conta il numero di spazi presenti in una stringa. Inoltre, controlla se ci sono caratteri di redirezione come > e < 
**incrementa il contatore solo se non ci sono altri caratteri di redirezione vicini.*/
int	ft_count_space(char *line)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i - 1] != '<' && line[i - 1] != '>')
				count++;
			else if (line[i + 1] != '<' && line[i + 1] != '>')
				count++;
		}
	}
	return (count);
}

/*aggiunge spazi alla stringa line in posizioni specifiche, in modo da separare i caratteri di redirezione da eventuali altri caratteri presenti nella stringa. 
**Restituisce l'indice della prossima posizione vuota in line.*/
static int	ft_add_space(char *tmp, int i, char *line, int j)
{
	if (tmp[i - 1] != '<' && tmp[i - 1] != '>')
		line[j++] = ' ';
	line[j] = tmp[i];
	if (tmp[i + 1] != '<' && tmp[i + 1] != '>')
		line[++j] = ' ';
	return (j);
}

/* prepara una nuova stringa aggiungendo spazi per separare i caratteri di redirezione. Restituisce la nuova stringa.*/
static char	*ft_preparate_space(char *tmp)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	j = 0;
	line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + \
				(ft_count_space(tmp) * 2) + 1));
	if (!line)
		return (0);
	while (tmp[++i])
	{
		if (tmp[i] == '>' || tmp[i] == '<')
			j = ft_add_space(tmp, i, line, j);
		else
			line[j] = tmp[i];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/*imposta le informazioni necessarie per l'esecuzione dei comandi, come i token, le priorità, le operazioni logiche e le redirezioni. 
**Inoltre, libera la memoria allocata per le matrici tmp e tmp_value*/
void	ft_set_info(char **tmp, t_all *main, char *copy_line, int count)
{
	char	**tmp_value;
	int		i;
	bool	first;

	first = TRUE;
	tmp_value = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp_value)
		return ;
	i = -1;
	while (tmp[++i])
	{
		tmp_value[i] = ft_find_token(tmp[i], main, first);
		first = FALSE;
	}
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_set_op_logic(copy_line, main->token);
	ft_set_priority(copy_line, main, 0);
	ft_set_redirections(main->token);
	ft_free_matrix(tmp_value);
	ft_free_matrix(tmp);
}

/*analizza la stringa di input line, prepara una copia della stringa con spazi per separare i caratteri di redirezione
**chiama ft_set_info per impostare le informazioni necessarie. 
**gestisce eventuali errori di parsing e controlla se ci sono più comandi concatenati da operatori logici come && e ||.*/
void	ft_parsing(char *line, t_all *main)
{
	char	**tmp;
	char	*copy_line;
	int		i;
	int		count;

	i = 0;
	count = 1;
	copy_line = ft_preparate_space(line);
	main->copy_line = ft_strdup(copy_line);
	while (copy_line[i])
	{
		i = ft_support_parsing(copy_line, main, i);
		if (copy_line[i] == 38 || copy_line[i] == 59 || copy_line[i] == 124)
		{
			if (copy_line[i + 1] == 38 || copy_line[i + 1] == 124 || \
		copy_line[i] == 59 || (copy_line[i] == 124 && copy_line[i - 1] != 124))
				count++;
			copy_line[i] = 127;
		}
		i++;
	}
	tmp = ft_split_original(copy_line, 127);
	ft_set_info(tmp, main, main->copy_line, count);
	free(copy_line);
}
