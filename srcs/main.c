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
	ft_printf("MGRN(Usage: ./ft_ls -[l][a][r][R][t])\n");
	ft_printf("\tMRED(-l)\tMRED(coMGRN(loMYLW(rs)\n");
	ft_printf("\tMRED(-a)\tMBLU(Print MPRP(ways)\n");
	ft_printf("\tMRED(-r)\tMYLW(Number of) MBLU(steps)\n");
	ft_printf("\tMRED(-R)\t ̶D̶o̶ ̶n̶o̶t̶ ̶p̶r̶i̶n̶t̶ ̶i̶n̶p̶u̶t ̶d̶a̶t̶a̶\n");
	ft_printf("\tMRED(-t)\tMPRP(All MBLU(data)\n");
	exit(0);
}

void parsing_dirs(int argc, char **argv, int i)
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

void parsing_flags(int argc, char **argv)
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
				else
					errrorrororo();
			}
		}
		else
			break ;
	}
		parsing_dirs(argc, argv, i);
}

void			parsing_argc(int argc, char **argv)
{
	parsing_flags(argc, argv);
}

void print_argc(void) {
	ft_printf("l : %d\nR : %d\nt : %d\nr : %d\na : %d\n",
	st.cv.flag_l, st.cv.flag_R, st.cv.flag_t, st.cv.flag_r, st.cv.flag_a);
}


int		is_file(char *filename, t_files **argc)
{
	struct stat buf;

	if (lstat(filename, &buf))
		return 0;
	else
		add_file(argc, filename, &buf, filename);
	return (1);
}

void read_argc(t_files *files, t_dirs *dirs)
{
	if (files)
	{
		files = sort_list_by_names(files);
		print_files(files);
		del_files(&files);
		st.is_name = true;
		if (dirs)
		ft_printf("\n");
	}
}

void check_dirs(t_dirs *dirs)
{
	t_dirs *tmp;
	t_files *argc;

	argc = NULL;
	tmp = dirs;
	while (tmp)
	{
		if (!is_dir(tmp->name))
		{
			if (!is_file(tmp->name, &argc))
			{
				ft_printf("MRED(%s isnt a folder/file!)\n", tmp->name);
				del_elem(&dirs, tmp);
			}
			else
				del_elem(&dirs, tmp);
		}
		tmp = tmp->next;
	}
	read_argc(argc, dirs);
	st.dirs = dirs;
}

int				main(int argc, char **argv)
{
	st.dirs = NULL;
	parsing_argc(argc, argv);
	st.dirs = sort_dirs_by_names(st.dirs);
	check_dirs(st.dirs);
	//print_list(st.dirs);
	read_data();
	//system("leaks ft_ls");
}
