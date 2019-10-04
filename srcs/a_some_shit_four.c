/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_some_shit_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:38:14 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:38:15 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	parsing_dirs(int argc, char **argv, int i)
{
	if (i == argc)
		add_elem(&st.dirs, ".");
	else
	{
		while (i < argc)
		{
			add_elem(&st.dirs, argv[i]);
			i++;
		}
	}
}

bool	check_second_symbol(char str)
{
	const char	*symbols = "laRrth-";
	int			j;

	j = -1;
	while (symbols[++j])
	{
		if (symbols[j] == str)
			return (true);
	}
	return (false);
}

void	is_real_shit(char **argv, int i, int j)
{
	if (argv[i][j] == 'l')
		st.cv.flag_l = true;
	else if (argv[i][j] == 'a')
		st.cv.flag_a = true;
	else if (argv[i][j] == 'R')
		st.cv.flag_R = true;
	else if (argv[i][j] == 't')
		st.cv.flag_t = true;
	else if (argv[i][j] == 'r')
		st.cv.flag_r = true;
	else if (argv[i][j] == 'h')
		st.cv.flag_h = true;
	else if (argv[i][j] == '-')
	{
		if (check_second_symbol(argv[i][j + 1]))
			errrorrororo();
	}
	else
		errrorrororo();
}

void	parsing_flags(int argc, char **argv)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' && check_second_symbol(argv[i][j + 1]))
		{
			while (argv[i][++j])
				is_real_shit(argv, i, j);
		}
		else
			break ;
	}
	parsing_dirs(argc, argv, i);
}

void	parsing_argc(int argc, char **argv)
{
	parsing_flags(argc, argv);
}
