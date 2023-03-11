/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:07 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*Questo codice contiene alcune funzioni utilizzate per l'espansione di variabili in una shell. 
**Queste funzioni cercano variabili all'interno di una stringa, sostituiscono le variabili con i loro valori corrispondenti e restituiscono la stringa modificata.*/

/* libera la memoria allocata per tre stringhe passate come argomenti.*/
static void	ft_free_expand(char *str, char *str1, char *str2)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

/*cerca la stringa word all'interno dell'array di stringhe env. 
**In particolare, cerca una stringa dell'array che inizia con la stringa word seguita dal carattere '='*/
static char	*ft_search_word(char *word, char **env)
{
	char	*tmp;
	char	*rtr;

	tmp = ft_strjoin(word, "=");
	free(word);
	rtr = ft_searchstrchr(tmp, env);
	free (tmp);
	return (rtr);
}

/*sostituisce una variabile di ambiente con il suo valore all'interno di una stringa, a partire dalla posizione in cui è presente il carattere '$'. 
**Se la variabile non esiste, viene sostituita con una stringa vuota.*/
char	*ft_change_var_in_dollar(int start, int l, char *str, t_all *main)
{
	char		*first_part;
	char		*second_part;
	char		*word;
	char		*insert_word;

	first_part = ft_substr(str, 0, start - 1);
	second_part = ft_substr(str, start + l, ft_strlen(str));
	word = ft_substr(str, start, l);
	insert_word = ft_search_word(word, main->copy_env);
	if (insert_word == NULL)
	{
		insert_word = (char *)malloc(sizeof(char) * 1);
		if (!insert_word)
		{
			ft_free_expand(word, first_part, second_part);
			return (NULL);
		}
		insert_word[0] = '\0';
	}
	word = ft_strjoin(first_part, insert_word);
	ft_free_expand(insert_word, first_part, str);
	str = ft_strjoin(word, second_part);
	ft_free_expand(NULL, second_part, word);
	return (str);
}

/*ha lo scopo di eliminare un paio di parentesi graffe attorno alla variabile da espandere*/
static void	ft_expand_support(char *line, int i)
{
	char	*tmp;

	line[i] = 127;
	while (line[i] != '}')
		i++;
	line[i] = 127;
	tmp = ft_strdup(line);
	free(line);
	line = ft_strtrim2(tmp, 127);
	free(tmp);
}

/*scansiona la stringa in input alla ricerca di caratteri speciali come il carattere $
**chiama la funzione ft_change_var_in_dollar per sostituire le variabili di ambiente corrispondenti con il loro valore. 
**Se la stringa contiene una variabile espansa tra ${}, viene chiamata la funzione ft_expand_support per gestirla. 
**la funzione restituisce la stringa espansa.*/
char	*ft_expand_doll(char *line, t_all *main, int i)
{
	char	*tmp;
	int		start;
	int		l;

	start = i;
	l = 0;
	if (line[i] == '{')
		ft_expand_support(line, i);
	while (line[++i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'' \
	&& line[i] != '$' && line[i] != 62 && line[i] != 60)
		l++;
	tmp = ft_strdup(line);
	free(line);
	if (tmp[start] == '?')
	{
		line = ft_itoa(g_exit);
		free(tmp);
	}
	else
		line = ft_change_var_in_dollar(start, l + 1, tmp, main);
	return (line);
}
