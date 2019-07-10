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
	ft_printf("\t\tMRED(-l)\tLong data format\n");
	ft_printf("\t\tMRED(-a)\tContains File/Directories starts w/ '.'\n");
	ft_printf("\t\tMRED(-r)\tReverse sort by names\n");
	ft_printf("\t\tMRED(-R)\tContains All dirs in all dirs\n");
	ft_printf("\t\tMRED(-t)\tSort by time\n");
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

bool check_second_symbol(char str)
{
	const char *symbols = "laRrth-";
	int j;

	j = -1;
	while (symbols[++j])
	{
		if (symbols[j] == str)
				return (true);
	}
	return (false);
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
		if (argv[i][j] == '-' && check_second_symbol(argv[i][j + 1]))
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
				else if (argv[i][j] == '-')
				{
					if (check_second_symbol(argv[i][j + 1]))
						errrorrororo();
				}
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

t_dirs *read_argc(t_files *files, t_dirs *dirs)
{
	char *tmp;
	if (files)
	{
		if (st.cv.flag_t)
			files = sort_list_by_time(files);
		files = sort_list_by_names(files);
		print_files(files, dirs);
		del_files(&files);
		st.is_name = true;
		if (dirs)
			ft_printf("\n");
	}
	return (dirs);
}

void check_dirs(t_dirs *dirs)
{
	t_dirs *tmp;
	t_files *argc;

	argc = NULL;
	tmp = dirs;

		st.is_name = true;
	while (tmp)
	{
		if (!is_dir(tmp->name))
		{
			if (!is_file(tmp->name, &argc))
			{
				ft_printf("MRED(ft_ls: %s isnt a folder/file!)\n", tmp->name);
				del_elem(&dirs, tmp);
			}
			else
				del_elem(&dirs, tmp);
		}
		tmp = tmp->next;
	}
	st.dirs = read_argc(argc, dirs);
}

int				main(int argc, char **argv)
{
	st.dirs = NULL;
	parsing_argc(argc, argv);
	if (st.cv.flag_t)
		st.dirs = sort_dirs_by_time(st.dirs);
	else
		st.dirs = sort_dirs_by_names(st.dirs);
	check_dirs(st.dirs);
	read_data();
}
