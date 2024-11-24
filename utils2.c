/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:55:01 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/22 18:00:40 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strchr(const char *s, int c)
{
    size_t    i;

    i = 0;
    while (i <= ft_strlen(s))
    {
        if (s[i] == (char)c)
            return ((char *) s + i);
        else
            i++;
    }
    return (NULL);
}
int	ft_isalnum(int c)
{
	return ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122));
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s2[i] == '\0')
		return (s1[i]);
	if (s1[i] == '\0')
		return (s2[i]);
	while (s1 && s2 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static int	len(int n)
{
	int				counter;
	unsigned int	number;

	counter = 1;
	number = n;
	if (n < 0)
	{
		number = n * -1;
		counter++;
	}
	while (number >= 10)
	{
		number /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	int				nb_digit;
	char			*str;
	int				i;
	unsigned int	number;

	number = n;
	nb_digit = len(n);
	i = nb_digit - 1;
	str = (char *)malloc((nb_digit + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[i] = '0';
	if (n < 0)
	{
		str [0] = '-';
		number = n * -1;
	}
	while (number > 0)
	{
		str[i--] = '0' + (number % 10);
		number /= 10;
	}
	str[nb_digit] = '\0';
	return (str);
}
