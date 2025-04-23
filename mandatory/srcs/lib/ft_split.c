/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:33 by raisufaj          #+#    #+#             */
/*   Updated: 2025/04/23 15:41:58 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static size_t	ft_count_word(const char *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	word;

	i = 0;
	count = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
			count = 0;
		else if (count == 0)
		{
			count = 1;
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

static void	ft_free(char **ptr, int c)
{
	int	i;

	i = 0;
	--c;
	while (i <= c)
		free(ptr[i++]);
	free(ptr);
}

static char	**ft_loop(char **ptr, const char *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	j;
	size_t	word_len;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_len = ft_word_len(&s[i], c);
			ptr[k] = malloc((word_len + 1) * sizeof(char));
			if (!ptr[k])
				return (ft_free(ptr, k), NULL);
			j = 0;
			while (j < word_len)
				ptr[k][j++] = s[i++];
			ptr[k++][j] = '\0';
		}
		else
			i++;
	}
	ptr[k] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!ptr)
		return (NULL);
	return (ft_loop(ptr, s, c));
}
