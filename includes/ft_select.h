/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:42:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/01 19:59:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>

# include <stdio.h>      //DELETE

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// extern char     PC;
// extern char     *UP;
// extern char     *BC;
// extern short    ospeed;


/*
** In the main.c file
*/

int				terminal_init_start(int argc, char **argv);
char			*start_selection(int argc, char **argv);

/*
** File errors_output.c
*/

int             usage(void);
int             terminal_errors(int flag);

/*
** File help_fucntions.c
*/

void		    *ft_xmalloc(size_t size);
char            *ft_straddsy(char *dest, char sy);

#endif