/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:30:49 by iruban            #+#    #+#             */
/*   Updated: 2019/10/04 19:30:49 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/libft.h"

void	errrorrororo(void)
{
	ft_printf("MGRN(Usage: ./ft_ls -[l][a][r][R][t])\n");
	ft_printf("\t\tMRED(-l)\tLong data format\n");
	ft_printf("\t\tMRED(-a)\tContains File/Directories starts w/ '.'\n");
	ft_printf("\t\tMRED(-r)\tReverse sort by names\n");
	ft_printf("\t\tMRED(-R)\tContains All dirs in all dirs\n");
	ft_printf("\t\tMRED(-t)\tSort by time\n");
	exit(0);
}

void	print_argc(void)
{
	ft_printf("l : %d\nR : %d\nt : %d\nr : %d\na : %d\n",
		g_gen.cv.flag_l, g_gen.cv.flag_r_big, g_gen.cv.flag_t, g_gen.cv.flag_r,
		g_gen.cv.flag_a);
}

int		main(int argc, char **argv)
{
	g_gen.dirs = NULL;
	parsing_argc(argc, argv);
	if (g_gen.cv.flag_t)
		g_gen.dirs = sort_dirs_by_time(g_gen.dirs);
	else
		g_gen.dirs = sort_dirs_by_names(g_gen.dirs);
	check_dirs(g_gen.dirs);
	read_data();
}
