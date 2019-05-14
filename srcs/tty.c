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