/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:44:06 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/20 19:34:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"
#include <stdbool.h>

static size_t	count_words(const char *s, char *c)
{
	unsigned int	words;
	bool			in_word;

	in_word = false;
	words = 0;
	while (*s)
	{
		if (ft_strchr(c, *s))
			in_word = false;
		else if (in_word == false)
		{
			words++;
			in_word = true;
		}
		s++;
	}
	return (words);
}

static void	filldest(char **dest, char *s, char *c)
{
	unsigned int	i;
	bool			in_word;

	in_word = false;
	i = 0;
	while (*s)
	{
		if (ft_strchr(c, *s))
		{
			in_word = false;
			*s = 0;
		}
		else if (in_word == false)
		{
			dest[i++] = s;
			in_word = true;
		}
		s++;
	}
}

char	**ft_strtok(char *s, char *tok)
{
	char			**dest;
	unsigned int	n_words;

	n_words = count_words(s, tok);
	dest = ft_calloc(sizeof(char *), (n_words + 1));
	if (dest == NULL)
		return (NULL);
	filldest(dest, s, tok);
	return (dest);
}
