/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:42:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/07 20:16:38 by sschmele         ###   ########.fr       */
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
	short			underline;
	unsigned int	x;
	unsigned int	y;
	size_t			len;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

/*
** File terminal_changes.c
*/

int					terminal_init_start(int argc, char **argv);
void				reset_canonical_input(struct termios save_terminal_mode);
void				make_fullscreen(void);
void				reset_terminal_mode(void);

/*
** File selection_process.c
*/

char				*start_selection(int argc, const char **argv);

/*
** File args_initiation.c
*/

t_args				*save_arguments(int argc, const char **argv);
t_args				*init_first_argument(const char *argument);
void				init_next_argument(t_args *current,
						const char *argument, short flag);
void				sort_arguments(t_args *list, int total); //make sorting

/*
** File args_processing.c
*/

int					args_total(const t_args *list);
void				position_and_output_arguments(const t_args *list);
t_args				*delete_argument(t_args *list, t_args *selected);
void				clean_arguments(t_args *list);

/*
** File underline_inverse_video.c
*/

void				underline_on(void);
void				underline_off(void);

/*
** File readline.c
*/

char				*read_commands(t_args *list);
int					key_hook(void);
void				move_up_down_right_left(t_args *list, char flag);

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