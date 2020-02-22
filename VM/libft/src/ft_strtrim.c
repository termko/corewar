/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 23:46:48 by vellery-          #+#    #+#             */
/*   Updated: 2018/12/25 22:19:40 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	iswhite(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static char	*funcret(char *str)
{
	str = (char*)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	return (ft_strcpy(str, ""));
}

char		*ft_strtrim(char const *s)
{
	int		i;
	char	*str;
	int		k;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	i = 0;
	while (iswhite(s[i]) && s[i])
		i++;
	if (s[i] == '\0')
		return (funcret((char*)s));
	while (iswhite(s[len]) && s[len])
		len--;
	if (!(str = (char*)malloc(sizeof(char) * (len - i + 2))))
		return (NULL);
	k = 0;
	while (i <= len)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
