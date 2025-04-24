/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:33 by raisufaj          #+#    #+#             */
/*   Updated: 2025/04/24 14:03:47 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static size_t	ft_count_word(const char *str, char c)
{
	size_t	i;
	size_t	in_word;
	size_t	word;

	i = 0;
	in_word = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			word++;
		}
		i++;
	}
	return (word);
}

static size_t	ft_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_free(char **ptr, int strs)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (i < strs)
		free(ptr[i++]);
	free(ptr);
}

static char	**fill_words(char **result, const char *s, char c)
{
	size_t	i;
	size_t	res_index;
	size_t	wd_index;
	size_t	wd_len;

	i = 0;
	res_index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wd_len = ft_word_len(&s[i], c);
			result[res_index] = malloc((wd_len + 1) * sizeof(char));
			if (!result[res_index])
				return (ft_free(result, res_index), NULL);
			wd_index = 0;
			while (wd_index < wd_len)
				result[res_index][wd_index++] = s[i++];
			result[res_index++][wd_index] = '\0';
		}
		else
			i++;
	}
	result[res_index] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!ptr)
		return (NULL);
	return (fill_words(ptr, s, c));
}
