/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iruban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:59:48 by iruban            #+#    #+#             */
/*   Updated: 2019/03/19 12:59:50 by iruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
# include "../libft/includes/ft_printf.h"
#include "../libft/includes/libft.h"

void			errrorrororo(void)
{
	ft_printf("MGRN(Usage: ./ft_ls [-l][-a][-r][-R][-t])\n");
	ft_printf("\tMRED(-l)\tMRED(coMGRN(loMYLW(rs)\n");
	ft_printf("\tMRED(-a)\tMBLU(Print MPRP(ways)\n");
	ft_printf("\tMRED(-r)\tMYLW(Number of) MBLU(steps)\n");
	ft_printf("\tMRED(-R)\t ̶D̶o̶ ̶n̶o̶t̶ ̶p̶r̶i̶n̶t̶ ̶i̶n̶p̶u̶t ̶d̶a̶t̶a̶\n");
	ft_printf("\tMRED(-t)\tMPRP(All MBLU(data)\n");
	exit(0);
}

void			parsing_argc(int argc, char **argv)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][j] == '-')
		{
			while (argv[i][++j])
			{
				if (argv[i][j] == 'l')
					g_flags.flag_l = true;
				else if (argv[i][j] == 'a')
					g_flags.flag_a = true;
				else if (argv[i][j] == 'R')
					g_flags.flag_R = true;
				else if (argv[i][j] == 't')
					g_flags.flag_t = true;
				else if (argv[i][j] == 'r')
					g_flags.flag_r = true;
				else
					errrorrororo();
			}
		}
		else
			errrorrororo();
	}
}

void print_argc(void) {
	ft_printf("l : %d\nR : %d\nt : %d\nr : %d\na : %d\n",
	g_flags.flag_l, g_flags.flag_R, g_flags.flag_t, g_flags.flag_r, g_flags.flag_a);
}

int				main(int argc, char **argv)
{
	parsing_argc(argc, argv);
	print_argc();



	exit(0);
}
