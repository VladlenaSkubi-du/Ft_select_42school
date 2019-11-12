/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_changes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:16:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** The main functionality starts from here, because we need to reset the
** terminal mode
** By "tcgetattr(STDIN_FILENO, &tty) < 0" we check if all the changes
** were launched.
*/

int				terminal_init_start(int argc, char **argv)
{
	struct termios	tty;
	struct termios	save_terminal_mode;
	char			*result;

	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		return (-1);
	save_terminal_mode = tty;
	tty.c_lflag &= ~(ICANON | ECHO | ISIG); //add ECHO and ISIG
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty) < 0)
		exit(1);
	if (tcgetattr(STDIN_FILENO, &tty) < 0 ||
		((tty.c_lflag & (ICANON | ECHO | ISIG) || //add ECHO and ISIG
		tty.c_cc[VMIN] != 1 || tty.c_cc[VTIME] != 1)))
	{
		reset_canonical_input(save_terminal_mode);
		return (-1);
	}
	result = start_selection(argc, (const char**)argv);
	reset_canonical_input(save_terminal_mode);
	if (result != NULL)
		ft_putendl_fd(result, 1);
	free(result);
	return (0);
}

void			reset_canonical_input(struct termios save_terminal_mode)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &save_terminal_mode) != 0)
	{
		ft_putstr_fd("Can't change terminal back. ", 2);
		ft_putendl_fd("You should reset the terminal", 2);
		exit(1);
	}
}

/*
** "tgetstr("ti", &buffer)" - function changes the pointer of buffer;
** `ti' - String of commands to put the terminal into whatever special
** modes are needed or appropriate for programs that move the cursor
** nonsequentially around the screen;
** `vi' - String to make the cursor invisible;
** `cl' - String to clear the entire screen and
** put cursor at upper left corner;
*/

void			make_fullscreen(void)
{
	char		buf[50];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ti", &buffer), 1, ft_putint);
	tputs(tgetstr("vi", &buffer), 1, ft_putint);
	tputs(tgetstr("cl", &buffer), 1, ft_putint);
	buffer = buf;
}

/*
** "tgetstr("ti", &buffer)" - function changes the pointer of buffer;
** `te' - String to return terminal to settings for sequential output;
** `ve' - String to return the cursor to normal.
*/

void			reset_terminal_mode(void)
{
	char		buf[50];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ve", &buffer), 1, ft_putint);
	tputs(tgetstr("te", &buffer), 1, ft_putint);
	buffer = buf;
}
