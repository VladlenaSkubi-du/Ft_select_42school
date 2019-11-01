/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/01 20:47:35 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		ft_putint(int c)
{
	return (write(1, &c, 1));
}

static int		key_hook(void)
{
    char		buffer[4];

	ft_bzero(buffer, 4);
    read(STDIN_FILENO, buffer, 3);
    return (*(unsigned int*)buffer);
}

char			*start_selection(int argc, char **argv)
{
	char		result[20];
	int			key;
	char		buffer[10]; //for try
	
	tputs(tgetstr("cl", &buffer), 1, putchar);
	while (1)
	{
		key = key_hook();
		ft_putnbr(key);
		if (key == '\033' || key == '\n')
			break ;
		// read(STDIN_FILENO, buffer, 3); //start using tremcap library
		// if (tgetflag(buffer)
		result = ft_straddsy(result, key);
	}
	return (result);
}

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
	tty.c_lflag &= ~(ICANON); //add ECHO and ISIG
	tty.c_cc[VMIN] = 3;
	tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty) < 0)
		exit(1);	
	if (tcgetattr(STDIN_FILENO, &tty) < 0 || ((tty.c_lflag & (ICANON) || //add ECHO and ISIG
		tty.c_cc[VMIN] != 3 || tty.c_cc[VTIME] != 1)))
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &save_terminal_mode);
		return (-1);
	}
	result = start_selection(argc, argv);
	tcsetattr(STDIN_FILENO, TCSANOW, &save_terminal_mode);
	if (result != NULL)
		ft_putendl_fd(result, 1);
	free(result);
	return (0);
}

int				main(int argc, char **argv)
{
	char			*termtype;
	char			*room_tremtype;

	if (!isatty(STDIN_FILENO))
		return (1);
	// if (argc < 2)
	// 	return (usage());
	room_tremtype = ft_xmalloc(1); //на стеке выделить 2048 для совместимости со старыми версиями программ
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_tremtype, termtype) != 1)	
		return (terminal_errors(0));
	if (terminal_init_start(argc, argv) < 0)
		return (terminal_errors(1));
	return (0);
}
