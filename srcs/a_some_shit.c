/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:25:28 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:25:29 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	res = ft_strnew(n);
	if (res)
		while (i < n)
		{
			res[i] = s1[i];
			i++;
		}
	return (res);
}

char	*privet_first(char *qqq, char *str)
{
	char *jopa;
	char *tmp;

	qqq = ft_strndup(&str[4], 7);
	jopa = ft_strndup(&str[20], 4);
	tmp = qqq;
	qqq = ft_strjoin(qqq, " ");
	free(tmp);
	tmp = qqq;
	qqq = ft_strjoin(qqq, jopa);
	free(tmp);
	free(jopa);
	return (qqq);
}

char	*privet_second(char *qqq, char *str)
{
	char *jopa;
	char *tmp;

	qqq = ft_strndup(&str[4], 6);
	jopa = ft_strndup(&str[10], 6);
	tmp = qqq;
	qqq = ft_strjoin(qqq, jopa);
	free(tmp);
	free(jopa);
	return (qqq);
}

char	*privet(char *str, long all_time)
{
	long t;
	long half_year;
	char *qqq;

	t = (long)time(NULL);
	half_year = 15768000;
	qqq = NULL;
	if (t - all_time > half_year)
		qqq = privet_first(qqq, str);
	else
		qqq = privet_second(qqq, str);
	return (qqq);
}

char	*pars_data(char *str, long all_time)
{
	char *qqq;

	qqq = privet(str, all_time);
	return (qqq);
}
