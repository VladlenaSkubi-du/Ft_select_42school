/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:42:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/05 20:37:41 by sschmele         ###   ########.fr       */
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
# include <string.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// extern char     PC;
// extern char     *UP;
// extern char     *BC;
// extern short    ospeed;

typedef struct		s_args
{
	char			*arg;
	short			selected;
	short			cursor;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;


/*
** File terminal_changes.c
*/

int					terminal_init_start(int argc, char **argv);
void				reset_canonical_input(struct termios save_terminal_mode);
char				*start_selection(int argc, char **argv);
char				*read_commands(t_args *list);
int					key_hook(void);

/*
** File args_processing.c
*/

t_args				*save_arguments(int argc, char **argv);
void				init_argument(t_args *current, char *argument, short flag);
void				output_arguments(t_args *list);
void				clean_arguments(t_args *list);

/*
** File errors_output.c
*/

int             	usage(void);
int             	terminal_errors(int flag);

/*
** File help_fucntions.c
*/

void		    	*ft_xmalloc(size_t size);
char            	*ft_straddsy(char *dest, char sy);
int					ft_putint(int c);

#endif