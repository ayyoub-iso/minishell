/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:32:21 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/22 17:24:48 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	if (dst == src)
		return (dst);
	pdst = (char *)dst;
	psrc = (const char *)src;
	if ((pdst == NULL) && (psrc == NULL))
		return (NULL);
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}


static size_t	counter(const char *str, char spliter)
{
	size_t	len;
	size_t	count;
	size_t	i;

	len = ft_strlen(str);
	count = 0;
	i = 0;
	while (i < len)
	{
		while (i < len && str[i] == spliter)
			i++;
		while (i < len && str[i] != spliter)
			i++;
		if (i > 0 && str[i - 1] != spliter)
			count++;
	}
	return (count);
}

static void	free_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	skip_count(const char *str, char del, size_t *i, size_t *subl)
{
	size_t	j;

	j = 0;
	while (str[*i] && str[*i] == del)
		(*i)++;
	while (str[j + *i] && str[j + *i] != del)
		j++;
	*subl = j;
}

char	**ft_split(const char *str, char spliter)
{
	size_t	string_index;
	size_t	i;
	size_t	sub_len;
	char	**strings;

	if (!str)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (counter(str, spliter) + 1));
	if (!strings)
		return (NULL);
	string_index = 0;
	i = 0;
	while (str[i])
	{
		skip_count(str, spliter, &i, &sub_len);
		if (i >= ft_strlen(str))
			break ;
		strings[string_index] = (char *)malloc(sub_len + 1);
		if (!strings[string_index])
			return (free_tab(strings, string_index), NULL);
		ft_memcpy(strings[string_index], str + i, sub_len);
		strings[string_index++][sub_len] = '\0';
		i += sub_len;
	}
	return (strings[string_index] = NULL, strings);
}
