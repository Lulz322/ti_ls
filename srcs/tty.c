#include "../includes/ft_ls.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

int tty(int max_size)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col / max_size - 2);
}

void	set_all_true(t_files *tmp)
{
	t_files *start;

	start = tmp;
	while (start)
	{
		start->is_dev = true;
		start = start->next;
	}
}

void	check_majors(t_files *tmp)
{
	t_files *start;

	start = tmp;
	while (start)
	{
		if (start->flags[0] == 'c' || start->flags[0] == 'b')
			set_all_true(tmp);
		start = start->next;
	}
}